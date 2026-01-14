
# ============================
# Flaskアプリ本体
# ============================

from flask import Flask, render_template, abort
from flask import send_from_directory
from flask import send_file

# C++コードをHTMLに色付き表示するためのライブラリ
from pygments import highlight
from pygments.lexers import CppLexer
from pygments.formatters import HtmlFormatter

# ファイル操作・補助ライブラリ
import zipfile
import json
import os
import io
import re

#Flaskアプリ作成
app = Flask(__name__)

# ============================
# パス・設定関連
# ============================

# このファイル (app.py) のあるディレクトリ
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# 授業ファイル (第1回.cpp等) を置くディレクトリ
LESSON_DIR = os.path.join(BASE_DIR, "lessons")

# 授業タイトルなどのメタ情報(JSON)
META_FILE = os.path.join(BASE_DIR, "meta", "lesson_meta.json")

# 授業メタデータ読み込み
# 例：{"1": "Hello World", "2": "for文"}
with open(META_FILE, "r", encoding="utf-8") as f:
    LESSON_META = json.load(f)


# ============================
# ユーティリティ関数
# ============================

def get_lesson_numbers():

    """
    lessons フォルダ内から
    「第◯回.cpp」「第◯回.txt」の番号を抽出する
    例: [1, 2, 3, 5]
    """

    files = os.listdir(LESSON_DIR)
    numbers = set()
    for f in files:
        match = re.match(r"第(\d+)回\.(cpp|txt)", f)
        if match:
            numbers.add(int(match.group(1)))
    return sorted(numbers)


# ============================
# ルーティング
# ============================

@app.route("/")
def index():
    """
    トップページ
    ・授業一覧を表示
    ・ダウンロードリンク(zip)
    """
    
    # 最大授業数
    number = 7  
    lesson_numbers = get_lesson_numbers()
    
    # 授業番号とタイトルをまとめたリストを作成
    lessons = [
        {"number": i, "title": LESSON_META.get(str(i), "")}
        for i in lesson_numbers
    ]
    
    
    return render_template("index.html", lessons=lessons, number=number)


@app.route("/lesson/<int:number>")
def show_lesson(number):
    """
    各授業ページ
    ・C++コードをシンタックスハイライトして表示
    """
    filename = f"第{number}回.cpp"
    filepath = os.path.join(LESSON_DIR, filename)

    # ファイルが存在しない場合は404
    if not os.path.exists(filepath):
        abort(404, "Lesson not found")

    # C++コードを読み込む
    with open(filepath, "r", encoding="utf-8") as f:
        code = f.read()

    # PygmentsでコードをHTMLに変換（色付き）
    formatter = HtmlFormatter(
        linenos=True,
        cssclass="codehilite",
        style="monokai"
    )
    highlighted_code = highlight(code, CppLexer(), formatter)

    lesson_numbers = get_lesson_numbers()

    return render_template(
        "lesson.html",
        number=number,                      # 第〇回
        code=highlighted_code,              # 色付きコード
        lessons=lesson_numbers,             # ナビ用
        title=LESSON_META.get(str(number), "") 
    )

@app.route("/download/<int:number>/<filetype>")
def download_lesson(number, filetype):
    """
    単体ダウンロード
    ・cpp / txt を指定してダウンロード
    """
    if filetype not in ["cpp", "txt"]:
        abort(404)
    
    filename = f"第{number}回.{filetype}"
    filepath = os.path.join(LESSON_DIR, filename)

    if not os.path.exists(filepath):
        abort(404, "File not found")

    return send_from_directory(
        LESSON_DIR,
        filename,
        as_attachment=True
    )

@app.route("/download/all")
def download_all():
    """
    全授業一括ダウンロード
    ・すべての cpp / txt をZIPにまとめて返す
    """
    lesson_numbers = get_lesson_numbers()

    # メモリ上にZIPファイルを作成
    memory_file = io.BytesIO()


    with zipfile.ZipFile(memory_file, 'w', zipfile.ZIP_DEFLATED) as zf:
        for i in lesson_numbers:
            for ext in ["cpp", "txt"]:
                filename = f"第{i}回.{ext}"
                filepath = os.path.join(LESSON_DIR, filename)

                if os.path.exists(filepath):
                    # ZIP内で拡張子ごとにフォルダ分け
                    zip_path = f"{ext}/{filename}"  # cpp/第1回.cpp, txt/第1回.txt
                    zf.write(filepath, arcname=zip_path)

    memory_file.seek(0)

    return send_file(
        memory_file,
        as_attachment=True,
        download_name="lessons.zip",  # ← attachment_filename ではなく download_name
        mimetype="application/zip"
    )

# ============================
# アプリ起動
# ============================

if __name__ == "__main__":
    # host=0.0.0.0 にすることで同一WiFi内からアクセス可能
    app.run(debug=True, host="0.0.0.0", port=5000)
