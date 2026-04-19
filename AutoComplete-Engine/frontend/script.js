let timeout = null;

// Fetch suggestions
function fetchSuggestions() {
    let query = document.getElementById("search").value;

    clearTimeout(timeout);

    timeout = setTimeout(async () => {

        if (!query) {
            document.getElementById("suggestions").innerHTML = "";
            return;
        }

        document.getElementById("loader").style.display = "block";

        try {
            let res = await fetch(`http://127.0.0.1:5000?q=${query}`);
            let data = await res.json();

            let box = document.getElementById("suggestions");
            box.innerHTML = "";

            data.forEach(word => {
                if (word.trim() === "") return;

                let div = document.createElement("div");
                div.className = "item";

                // fake frequency display
                let freq = Math.floor(Math.random() * 100);

                div.innerHTML = `
                    ${highlight(word, query)}
                    <span style="float:right;color:gray">${freq}</span>
                `;

                div.onclick = () => {
                    document.getElementById("search").value = word;
                    box.innerHTML = "";
                };

                box.appendChild(div);
            });

        } catch (e) {
            console.error(e);
        }

        document.getElementById("loader").style.display = "none";

    }, 200);
}

// Highlight match
function highlight(word, query) {
    let regex = new RegExp(query, "gi");
    return word.replace(regex, match => `<b>${match}</b>`);
}

// Dark mode
function toggleTheme() {
    document.body.classList.toggle("dark");
}

// Voice search
function startVoice() {
    let recognition = new (window.SpeechRecognition || window.webkitSpeechRecognition)();
    recognition.lang = "en-US";

    recognition.onresult = function(event) {
        let text = event.results[0][0].transcript;
        document.getElementById("search").value = text;
        fetchSuggestions();
    };

    recognition.start();
}