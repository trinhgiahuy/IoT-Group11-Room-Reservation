const getJSON = async url => {
    const response = await fetch(url, { method: 'GET'});
    if (!response.ok) throw new Error('Network response was not OK');
    return await response.json();
};

(async() => {

    const Status1 = document.getElementById('Status1');
    const Status2 = document.getElementById('Status2');
    
    /*const result = await getJSON('/static/frontpage.js')
    Status1.textContent = result[0].status;
    Status2.textContent = result[1].status;*/
})();

