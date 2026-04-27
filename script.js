// if button = clicked
// load different json
fetch("bfs.json")
.then(r => r.json())
.then(data => {


    const grid = document.getElementById("grid-bfs")
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
            cell.id = "bfs-c-" + i + "-" + j
            grid.appendChild(cell) //finally adds it
        }
    }
    const start = document.getElementById("bfs-c-"+data.root[0]+"-"+data.root[1])
    start.classList.add("start")

    const goal = document.getElementById("bfs-c-"+data.goal[0]+"-"+data.goal[1])
    goal.classList.add("goal")
    
    // heh
    // yup
    window.drawPath = function()
    {
        const grid = document.getElementById("grid-bfs");
        data.log.forEach((p,i)=>{
            setTimeout(()=>{
                const cell = document.getElementById("bfs-c-"+p.x+"-"+p.y)
                cell.classList.add("discover")

                // if grid.class = start || path. replace.
            },i*400)
        })
        const totalTime = data.log.length * 400; //wait until path is finished
            data.path.forEach((p,i)=>{
            setTimeout(()=>{
            if ( document.getElementById("bfs-c-"+p[0]+"-"+p[1]).classList.contains('goal') )
            {
                document.getElementById("bfs-c-"+p[0]+"-"+p[1]).classList.add('path');
                document.getElementById("bfs-c-"+p[0]+"-"+p[1]).classList.remove('goal');
            }
            if ( document.getElementById("bfs-c-"+p[0]+"-"+p[1]).classList.contains('start') )
            {
                document.getElementById("bfs-c-"+p[0]+"-"+p[1]).classList.add('path');
                document.getElementById("bfs-c-"+p[0]+"-"+p[1]).classList.remove('start');
            }
            const cell = document.getElementById("bfs-c-"+p[0]+"-"+p[1])
            cell.classList.add("path")
            },totalTime)
        })

    }
    window.resetPath = function()
    {
        const grid = document.getElementById("grid-bfs")
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
                cell.id = "bfs-c-" + i + "-" + j
                grid.appendChild(cell) //finally adds it
            }
        }
        const start = document.getElementById("bfs-c-"+data.root[0]+"-"+data.root[1])
        start.classList.add("start")

        const goal = document.getElementById("bfs-c-"+data.goal[0]+"-"+data.goal[1])
        goal.classList.add("goal")
    }
})