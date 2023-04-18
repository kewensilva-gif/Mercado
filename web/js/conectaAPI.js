let produtos = [];
const corpo = document.querySelector("#corpo");

async function conectaApi(){
    const conexao = await fetch("http://localhost:4000/produtos");
    produtos = await conexao.json();

    produtos.forEach((produto)=> {
        corpo.innerHTML += `
            <tr>
                <th scope="row">${produto.id}</th>
                <td>${produto.Nome}</td>
                <td>${produto.Quantidade}</td>
                <td>${produto.Marca}</td>
                <td>R$${produto.Custo}</td>
                <td>R$${produto.Venda}</td>
            </tr>
        `
    })
}
conectaApi()