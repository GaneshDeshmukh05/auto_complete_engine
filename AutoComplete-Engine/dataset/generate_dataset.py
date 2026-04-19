from wordfreq import zipf_frequency
import wordfreq

words = wordfreq.top_n_list("en", 10000000)

with open("backend/dictionary.txt", "w", encoding="utf-8") as f:
    for w in words:
        freq = int(zipf_frequency(w, "en") * 10000)
        if freq > 0:
            f.write(f"{w} {freq}\n")

print("Dataset generated successfully!")