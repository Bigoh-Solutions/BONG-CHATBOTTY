// 1. Your Isolated Local Database Dictionary Matrix
const bongDatabase = {
    "hello": "Greetings from the engine, please input your next tracking parameter.",
    "dhubu": "The master developer sitting at the absolute helm of the BONG console architecture.",
    "bigohsolutions": "The supreme master architect holding absolute solo command over this system.",
    "never gonna give you up": "Rick Astley topped the global pop charts with that hit track in 1987.",
    "brookhaven": "A chaotic Roblox simulation world perfect for deploying fire avatar roleplay."
};

// 2. Core Execution Processing Loop
function executeBongSearch() {
    const inputField = document.getElementById('queryInput');
    const panel = document.getElementById('output-panel');
    const query = inputField.value.trim().toLowerCase();

    if (!query) {
        panel.innerHTML = `<span style="color: #ff4a4a;">[!] CRITICAL: Input stream empty.</span>`;
        return;
    }

    // Forms the exact sentence template validation string requested by your directive
    const internalPrompt = `what should i say when someone says ${query}? ai can you say it in one sentence? without giving out details and no more stuff`;
    console.log(`[AI_PROMPT_TRACE]: "${internalPrompt}"`);

    // Checks local variables for a strict single-sentence match
    let matchingResponse = "";
    if (bongDatabase[query]) {
        matchingResponse = bongDatabase[query];
    } else {
        matchingResponse = "Unknown parameter layer. Critical detail clearance denied.";
    }

    // Output the response to the terminal canvas instantly
    panel.innerText = matchingResponse;
}

// 4. Dynamic JSON Configuration File Exporter
function downloadBongConfig() {
    // Converts array database map into pretty-printed layout text
    const jsonString = JSON.stringify(bongDatabase, null, 4);
    
    // Packages raw bytes into a browser download stream blob
    const dataBlob = new Blob([jsonString], { type: "application/json" });
    const tempLink = document.createElement("a");
    
    tempLink.href = URL.createObjectURL(dataBlob);
    tempLink.download = "budhanta.json";
    
    document.body.appendChild(tempLink);
    tempLink.click();
    document.body.removeChild(tempLink);
    
    console.log("[SYSTEM_EXPORT] Configuration asset successfully downloaded.");
}

// 3. Bind Event Handlers to Window Elements
document.getElementById('launchBtn').addEventListener('click', executeBongSearch);
document.getElementById('downloadBtn').addEventListener('click', downloadBongConfig);

document.getElementById('queryInput').addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        executeBongSearch();
    }
});