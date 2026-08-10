document.getElementById('downloadBtn').addEventListener('click', function() {
    // Replace with your actual file URL
    const fileUrl = 'DO-NOT-DELETE-ASSETS.zip';
    const link = document.createElement('a');
    link.href = fileUrl;
    link.download = 'DO-NOT-DELETE-ASSETS.zip';
    link.click();
});