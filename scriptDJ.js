// if button = clicked
// load different json
fetch("dijkstra.json")
.then(r => r.json())
.then(data => {
    const grid = document.getElementById("grid-dijkstra")
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
            cell.id = "dij-c-" + i + "-" + j
            grid.appendChild(cell) //finally adds it
        }
    }
    const start = document.getElementById("dij-c-"+data.root[0]+"-"+data.root[1])
    start.classList.add("start")

    const goal = document.getElementById("dij-c-"+data.goal[0]+"-"+data.goal[1])
    goal.classList.add("goal")
    
    // heh
    // yup
    window.drawPathp = function()
    {
        const grid = document.getElementById("grid-dijkstra");
        data.log.forEach((p,i)=>{
            setTimeout(()=>{
                const cell = document.getElementById("dij-c-"+p.x+"-"+p.y)
                cell.classList.add("discover")

                // if grid.class = start || path. replace.
            },i*400)
        })
        const totalTime = data.log.length * 400; //wait until path is finished
            data.path.forEach((p,i)=>{
            setTimeout(()=>{
            if ( document.getElementById("dij-c-"+p[0]+"-"+p[1]).classList.contains('goal') )
            {
                document.getElementById("dij-c-"+p[0]+"-"+p[1]).classList.add('path');
                document.getElementById("dij-c-"+p[0]+"-"+p[1]).classList.remove('goal');
            }
            if ( document.getElementById("dij-c-"+p[0]+"-"+p[1]).classList.contains('start') )
            {
                document.getElementById("dij-c-"+p[0]+"-"+p[1]).classList.add('path');
                document.getElementById("dij-c-"+p[0]+"-"+p[1]).classList.remove('start');
            }
            const cell = document.getElementById("dij-c-"+p[0]+"-"+p[1])
            cell.classList.add("path")
            },totalTime)
        })
    }
    window.resetPathp = function()
    {
        const grid = document.getElementById("grid-dijkstra")
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
                cell.id = "dij-c-" + i + "-" + j
                grid.appendChild(cell) //finally adds it
            }
        }
        const start = document.getElementById("dij-c-"+data.root[0]+"-"+data.root[1])
        start.classList.add("start")

        const goal = document.getElementById("dij-c-"+data.goal[0]+"-"+data.goal[1])
        goal.classList.add("goal")
    }
})