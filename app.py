from flask import Flask, render_template, abort
from flask import send_from_directory
from flask import send_file
from pygments import highlight
from pygments.lexers import CppLexer
from pygments.formatters import HtmlFormatter
import zipfile
import json
import os
import io
import re


app = Flask(__name__)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
LESSON_DIR = os.path.join(BASE_DIR, "lessons")
META_FILE = os.path.join(BASE_DIR, "meta", "lesson_meta.json")

with open(META_FILE, "r", encoding="utf-8") as f:
    LESSON_META = json.load(f)

def get_lesson_numbers():
    files = os.listdir(LESSON_DIR)
    numbers = set()
    for f in files:
        match = re.match(r"第(\d+)回\.(cpp|txt)", f)
        if match:
            numbers.add(int(match.group(1)))
    return sorted(numbers)


@app.route("/")
def index():
    lesson_numbers = get_lesson_numbers()
    lessons = [{"number": i, "title": LESSON_META.get(str(i), "")} for i in lesson_numbers]
    return render_template("index.html", lessons=lessons)


@app.route("/lesson/<int:number>")
def show_lesson(number):
    filename = f"第{number}回.cpp"
    filepath = os.path.join(LESSON_DIR, filename)

    if not os.path.exists(filepath):
        abort(404, "Lesson not found")

    with open(filepath, "r", encoding="utf-8") as f:
        code = f.read()

    formatter = HtmlFormatter(linenos=True, cssclass="codehilite", style="monokai")
    highlighted_code = highlight(code, CppLexer(), formatter)

    lesson_numbers = get_lesson_numbers()

    return render_template(
        "lesson.html",
        number=number,
        code=highlighted_code,
        lessons=lesson_numbers,
        title=LESSON_META.get(str(number), "") 
    )

@app.route("/download/<int:number>/<filetype>")
def download_lesson(number, filetype):
    if filetype not in ["cpp", "txt"]:
        abort(404)
    
    filename = f"第{number}回.{filetype}"
    filepath = os.path.join(LESSON_DIR, filename)

    if not os.path.exists(filepath):
        abort(404, "File not found")

    return send_from_directory(LESSON_DIR, filename, as_attachment=True)

@app.route("/download/all")
def download_all():
    lesson_numbers = get_lesson_numbers()

    memory_file = io.BytesIO()
    with zipfile.ZipFile(memory_file, 'w', zipfile.ZIP_DEFLATED) as zf:
        for i in lesson_numbers:
            for ext in ["cpp", "txt"]:
                filename = f"第{i}回.{ext}"
                filepath = os.path.join(LESSON_DIR, filename)
                if os.path.exists(filepath):
                    # ZIP 内でフォルダを分ける
                    zip_path = f"{ext}/{filename}"  # cpp/第1回.cpp, txt/第1回.txt
                    zf.write(filepath, arcname=zip_path)

    memory_file.seek(0)
    return send_file(
        memory_file,
        as_attachment=True,
        download_name="C++_授業.zip",  # ← attachment_filename ではなく download_name
        mimetype="application/zip"
    )

if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=5000)
