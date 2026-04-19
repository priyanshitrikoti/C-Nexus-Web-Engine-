// Update server time
async function updateTime() {
    try {
        const response = await fetch('/api/time');
        const data = await response.json();
        document.getElementById('time-display').textContent = data.time;
        document.getElementById('time-display').classList.add('pulse');
        setTimeout(() => {
            document.getElementById('time-display').classList.remove('pulse');
        }, 1000);
    } catch (error) {
        document.getElementById('time-display').textContent = 'Error fetching time';
    }
}

// Handle form submission
document.getElementById('userForm').addEventListener('submit', async function(e) {
    e.preventDefault();
    
    const formData = new FormData();
    formData.append('name', document.getElementById('name').value);
    formData.append('email', document.getElementById('email').value);
    formData.append('message', document.getElementById('message').value);
    
    try {
        const response = await fetch('/form', {
            method: 'POST',
            body: formData
        });
        
        const responseDiv = document.getElementById('form-response');
        responseDiv.style.display = 'block';
        responseDiv.innerHTML = '✅ Form submitted successfully!<br>Data: ' + 
            JSON.stringify(Object.fromEntries(formData), null, 2);
    } catch (error) {
        console.error('Error:', error);
    }
});

// Auto-update time every 5 seconds
setInterval(updateTime, 5000);

// Initial load
updateTime();

// Uptime counter
let startTime = Date.now();
setInterval(() => {
    const uptime = Math.floor((Date.now() - startTime) / 1000);
    const minutes = Math.floor(uptime / 60);
    const seconds = uptime % 60;
    document.getElementById('uptime').textContent = 
        `${minutes}m ${seconds}s`;
}, 1000);