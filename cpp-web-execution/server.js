const http = require('http');
const fs = require('fs');
const path = require('path');
const { exec } = require('child_process');

const server = http.createServer((req, res) => {
    if (req.url === '/' || req.url === '/index.html') {

        const indexPath = path.join(__dirname, 'index.html');
        fs.readFile(indexPath, (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Internal Server Error');
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data);
            }
        });
    } else if (req.url === '/ViewData' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            try {
                const { argument } = JSON.parse(body);
                exec(`./PatientData ${argument}`, (error, stdout, stderr) => {
                    if (error) {
                        res.writeHead(500, { 'Content-Type': 'text/plain' });
                        res.end('Internal Server Error');
                    } else {
                        const outputWithBreaks = stdout.replace(/\n/g, '<br>'); // Replace newline characters with <br> tags

                        res.writeHead(200, { 'Content-Type': 'application/json' });
                        res.end(JSON.stringify({ output: outputWithBreaks }));
                    }
                });
            } catch (error) {
                res.writeHead(400, { 'Content-Type': 'text/plain' });
                res.end('Bad Request');
            }
        });
    }
});

const PORT = process.env.PORT || 3001;
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});