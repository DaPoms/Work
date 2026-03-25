export function getList(addresses) {
  return `<!DOCTYPE html>
    <html>
      <head>
        <title>Address Book</title>
        <meta charset="utf-8">
      </head>
      <body>
        <h1>Address Book</h1>
        <table>
          <thead>
            <tr>
              <th>Id</th>
              <th>First Name</th>
              <th>Last Name</th>
              <th>delete</th>
            </tr>
          </thead>
          <tbody>
            ${addresses.map(createRow).join('')}
          </tbody>
        </table>
      </body>
    </html>`;
}

function createRow(address) {
  return `<tr>
    <td>${address.id}</td>
    <td>${address.firstname}</td>
    <td>${address.lastname}</td>
    <td><a href="/delete/${address.id}">delete</a></td>
  </tr>`;
}
