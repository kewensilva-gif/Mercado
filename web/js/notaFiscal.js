let contaJson = [];
const corpo = document.querySelector("#corpo");
const corpoConta = document.querySelector("#conta");

async function notaFiscalApi(){
    let produtosConexao = await fetch("http://localhost:3000/produtos");
    let contaConexao = await fetch("http://localhost:3000/conta");

    produtosJson = await produtosConexao.json();
    contaJson = await contaConexao.json();
   
    produtosJson.forEach((produto)=>{
        corpo.innerHTML += `
        <tr>
            <td>${produto.id}</td>
            <td>${produto.Nome}</td>
            <td>${produto.Marca}</td>
            <td>${produto.Quantidade}</td>
            <td>${produto.PrecoUnidade}</td>
            <td>${produto.PrecoTotal}</td>
        </tr>
    `
    })

    console.log(contaJson[0])
    corpoConta.innerHTML += `
    <div class="conta-item">
        <p class="bold">Qtde total de itens</p>
        <p>${contaJson[0].QuantidadeItens}</p>
    </div>
    <div class="conta-item">
        <p class="bold">Valor total R$</p>
        <p>${contaJson[0].Total}</p>
    </div>
    <div class="conta-item">
        <p class="bold">Pagamento R$</p>
        <p>${contaJson[0].Entrada}</p>
    </div>
    <div class="conta-item">
        <p class="bold">Valor a devolver R$</p>
        <p>${contaJson[0].Troco}</p>
    </div>
`
}

notaFiscalApi();