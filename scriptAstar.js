// if button = clicked
// load different json
fetch("astar.json")
.then(r => r.json())
.then(data => {
    const grid = document.getElementById("grid-astar")
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
            cell.id = "astar-c-" + i + "-" + j
            grid.appendChild(cell) //finally adds it
        }
    }
    const start = document.getElementById("astar-c-"+data.root[0]+"-"+data.root[1])
    start.classList.add("start")

    const goal = document.getElementById("astar-c-"+data.goal[0]+"-"+data.goal[1])
    goal.classList.add("goal")
    
    // heh
    // yup
    window.drawPatha = function()
    {
        const grid = document.getElementById("grid-astar");
        data.log.forEach((p,i)=>{
            setTimeout(()=>{
                const cell = document.getElementById("astar-c-"+p.x+"-"+p.y)
                cell.classList.add("discover")
            },i*400)
        })
        const totalTime = data.log.length * 400; //wait until path is finished
            data.path.forEach((p,i)=>{
            setTimeout(()=>{
            if ( document.getElementById("astar-c-"+p[0]+"-"+p[1]).classList.contains('goal') )
            {
                document.getElementById("astar-c-"+p[0]+"-"+p[1]).classList.add('path');
                document.getElementById("astar-c-"+p[0]+"-"+p[1]).classList.remove('goal');
            }
            if ( document.getElementById("astar-c-"+p[0]+"-"+p[1]).classList.contains('start') )
            {
                document.getElementById("astar-c-"+p[0]+"-"+p[1]).classList.add('path');
                document.getElementById("astar-c-"+p[0]+"-"+p[1]).classList.remove('start');
            }
            const cell = document.getElementById("astar-c-"+p[0]+"-"+p[1])
            cell.classList.add("path")
            },totalTime)
        })
        const gridItem = document.querySelector('.grid-container > :first-child');

        gridItem.classList.replace('old-class', 'new-class');

    }
    window.resetPatha = function()
    {
        const grid = document.getElementById("grid-astar")
        grid.replaceChildren()
        //rerun earlier code
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
                cell.id = "astar-c-" + i + "-" + j
                grid.appendChild(cell) //finally adds it
            }
        }
        const start = document.getElementById("astar-c-"+data.root[0]+"-"+data.root[1])
        start.classList.add("start")

        const goal = document.getElementById("astar-c-"+data.goal[0]+"-"+data.goal[1])
        goal.classList.add("goal")
    }
})