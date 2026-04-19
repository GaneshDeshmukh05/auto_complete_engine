from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

@app.route("/")
def autocomplete():
    query = request.args.get("q", "")
    print("\n[DEBUG] Query received:", query)

    if not query:
        return jsonify([])

    try:
        exe_path = os.path.abspath(
            os.path.join(BASE_DIR, "..", "backend", "app.exe")
        )

        print("[DEBUG] EXE path:", exe_path)
        print("[DEBUG] EXE exists:", os.path.exists(exe_path))

        # Run C++ program
        result = subprocess.check_output(
            [exe_path, query],
            text=True
        )

        print("[DEBUG] Raw output:\n", result)

        # Clean output (remove debug lines)
        lines = result.strip().split("\n")
        suggestions = [line for line in lines if not line.startswith("[")]

        print("[DEBUG] Clean suggestions:", suggestions)

        return jsonify(suggestions)

    except Exception as e:
        print("[ERROR]", str(e))
        return jsonify({"error": str(e)})

if __name__ == "__main__":
    app.run(port=5000)