async function loadCreations() {
    const response = await fetch('/my-creations');
    const data = await response.json();
    const tbody = document.getElementById('my-creations');
    tbody.innerHTML = '';
    data.creations.forEach(entry => {
                if (!entry.item) {
                    return;
                }

                const tr = document.createElement('tr');

                if (entry.type === 'document') {
                    tr.innerHTML = `
                        <td>document</td>
                        <td>${entry.item.id}</td>
                        <td>${entry.item.name}</td>
                        <td>-</td>
                        <td>${entry.item.contents}</td>
                    `;
                } else {
                    tr.innerHTML = `
                        <td>movie</td>
                        <td>${entry.item.id}</td>
                        <td>${entry.item.title}</td>
                        <td>${entry.item.duration}</td>
                        <td>-</td>
                    `;
                }
                tbody.appendChild(tr);
            });
}
loadCreations();

let maxAuthorsDiv = document.getElementById('max-authors');
let maxAuthorsValueDiv = document.getElementById('max-authors-value');

async function loadLargestNumberOfAuthors() {
    const response = await fetch('/largest-number-of-authors');
    const data = await response.json();

    maxAuthorsValueDiv.textContent = data.maxAuthors;

    maxAuthorsDiv.innerHTML = '';

    data.documents.forEach(entry => {
        const doc = entry.document;

        const div = document.createElement('div');
        div.textContent = `${doc.id} - ${doc.name} - ${doc.contents}`;
        maxAuthorsDiv.appendChild(div);
    });
}
loadLargestNumberOfAuthors();