import os
import json
import requests

# 获取环境变量
GITHUB_TOKEN = os.environ.get("GITHUB_TOKEN")
REPOSITORY = os.environ.get("REPOSITORY")  # 格式如: owner/repo

HEADERS = {
    "Authorization": f"Bearer {GITHUB_TOKEN}",
    "Accept": "vnd.github+json",
    "X-GitHub-Api-Version": "2022-11-28"
}

def fetch_traffic_data(endpoint):
    url = f"https://api.github.com/repos/{REPOSITORY}/traffic/{endpoint}"
    response = requests.get(url, headers=HEADERS)
    if response.status_code == 200:
        return response.json()
    else:
        print(f"Failed to fetch {endpoint}: {response.status_code}, {response.text}")
        return None

def update_history(filename, new_items):
    if not new_items:
        return
    
    # 读取现有的历史数据
    if os.path.exists(filename):
        with open(filename, "r", encoding="utf-8") as f:
            history = json.load(f)
    else:
        history = []

    # 转为字典以 timestamp 为主键进行去重合并
    history_dict = {item["timestamp"]: item for item in history}
    
    for item in new_items:
        ts = item["timestamp"]
        history_dict[ts] = item

    # 按时间排序
    sorted_history = sorted(history_dict.values(), key=lambda x: x["timestamp"])

    # 写回文件
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    with open(filename, "w", encoding="utf-8") as f:
        json.dump(sorted_history, f, indent=2, ensure_ascii=False)
    print(f"Successfully updated {filename} with {len(new_items)} records.")

if __name__ == "__main__":
    if not GITHUB_TOKEN or not REPOSITORY:
        raise ValueError("Missing GITHUB_TOKEN or REPOSITORY environment variables.")

    # 1. 抓取克隆数据 (Clones)
    clones_data = fetch_traffic_data("clones")
    if clones_data and "clones" in clones_data:
        update_history("data/clones_history.json", clones_data["clones"])

    # 2. 抓取浏览数据 (Views)
    views_data = fetch_traffic_data("views")
    if views_data and "views" in views_data:
        update_history("data/views_history.json", views_data["views"])
      Add archive_traffic.py script
