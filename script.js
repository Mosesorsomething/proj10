fetch("bfs.json")
.then(r => r.json())
.then(data => {

    const grid = document.getElementById("grid")

    const arr = data.arr

    for(let y=0;y<arr.length;y++){
        for(let x=0;x<arr[0].length;x++){

            const cell = document.createElement("div")
            cell.classList.add("cell")

            if(!arr[y][x]){
                cell.classList.add("wall")
            }

            cell.id = "c-"+(y+1)+"-"+(x+1)

            grid.appendChild(cell)
        }
    }

    const start = document.getElementById("c-"+data.root[0]+"-"+data.root[1])
    start.classList.add("start")

    const goal = document.getElementById("c-"+data.goal[0]+"-"+data.goal[1])
    goal.classList.add("goal")

    window.drawPath = function(){

        data.path.forEach((p,i)=>{
            setTimeout(()=>{
                const cell = document.getElementById("c-"+p[0]+"-"+p[1])
                cell.classList.add("path")
            },i*500)
        })

    }

})