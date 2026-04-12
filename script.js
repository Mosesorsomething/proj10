fetch("bfs.json")
.then(r => r.json())
.then(data => {


    const grid = document.getElementById("grid")
    const arr = data.arr;
    for(let i = 0; i < arr.length; i++)
    {
        for(let j = 0; j < arr[0].length; j++)
        {
            const cell = document.createElement("div");
            cell.classList.add("cell"); // creates cell
            if(arr[i][j])
            {
                cell.classList.add("wall")
            }
            cell.id = "c-" + i + "-" + j
            grid.appendChild(cell)
        }
    }
    const start = document.getElementById("c-"+data.root[0]+"-"+data.root[1])
    start.classList.add("start")

    const goal = document.getElementById("c-"+data.goal[0]+"-"+data.goal[1])
    goal.classList.add("goal")
    
    // heh
    // yup
    window.drawPath = function()
    {
        data.visited.forEach((p,i)=>{
            setTimeout(()=>{
                const cell = document.getElementById("c-"+p[0]+"-"+p[1])
                cell.classList.add("discover")
            },i*400)
        })
        const totalTime = data.visited.length * 400; //wait until path is finished
            data.path.forEach((p,i)=>{
            setTimeout(()=>{
            const cell = document.getElementById("c-"+p[0]+"-"+p[1])
            cell.classList.add("path")
            },totalTime)
        })
    }
})