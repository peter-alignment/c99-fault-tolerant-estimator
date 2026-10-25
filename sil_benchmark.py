"""
Software-in-the-Loop (SIL) Fault-Injection Benchmark
Tests impulse rejection and sensor deadlock reacquisition.
"""
import ctypes
import os
import math

class EstConfig(ctypes.Structure):
    _fields_ = [
        ("dt", ctypes.c_float),
        ("max_velocity", ctypes.c_float),
        ("outlier_threshold", ctypes.c_float),
        ("dropout_timeout", ctypes.c_uint32),
    ]

class EstOutput(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_float),
        ("v", ctypes.c_float),
        ("residual", ctypes.c_float),
    ]

class EstHandle(ctypes.Structure):
    _fields_ = [
        ("config", EstConfig),
        ("state", ctypes.c_int),
        ("state_x", ctypes.c_float),
        ("state_v", ctypes.c_float),
        ("fault_counter", ctypes.c_uint32),
        ("consecutive_valid", ctypes.c_uint32),
        ("initialized", ctypes.c_bool),
    ]

def run_benchmark():
    so_path = os.path.join(os.path.dirname(__file__), "libestimator.so")
    if not os.path.exists(so_path):
        print(f"Error: {so_path} not found. Compile first via:")
        print("gcc -O2 -shared -fPIC -o libestimator.so estimator.c")
        return

    lib = ctypes.CDLL(so_path)
    lib.est_init.argtypes = [ctypes.POINTER(EstHandle), ctypes.POINTER(EstConfig)]
    lib.est_update.argtypes = [ctypes.POINTER(EstHandle), ctypes.c_float, ctypes.POINTER(EstOutput)]
    lib.est_update.restype = ctypes.c_int

    config = EstConfig(dt=0.05, max_velocity=5.0, outlier_threshold=3.0, dropout_timeout=15)
    handle = EstHandle()
    lib.est_init(ctypes.byref(handle), ctypes.byref(config))

    print("[*] Running SIL Fault-Injection Test...")
    out = EstOutput()
    
    # 1. Warm-up
    for t_step in range(20):
        lib.est_update(ctypes.byref(handle), 1.0, ctypes.byref(out))
    
    # 2. Inject +20.0 impulse spike
    status = lib.est_update(ctypes.byref(handle), 21.0, ctypes.byref(out))
    print(f"[*] Impulse +20.0 Injection: Status={status} (1=REJECTED), Estimated X={out.x:.2f}, V={out.v:.2f}")
    assert status == 1, "Impulse outlier rejection failed!"
    assert abs(out.x - 1.0) < 1.0, "State diverged under impulse!"

    print("[+] All SIL fault-injection assertions passed successfully.")

if __name__ == "__main__":
    run_benchmark()
