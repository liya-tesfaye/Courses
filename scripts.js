
const todoInput = document.getElementById("todoInput");
const addButton = document.getElementById("addButton");
const todoList = document.getElementById("todoList");

const priorities = [
    "low-priority",
    "medium-priority",
    "high-priority"
];

function addTodo() {
    const todoText = todoInput.value.trim();

    if (todoText === "") {
        return;
    }

    const li = document.createElement("li");
    li.classList.add("todo-item", "medium-priority");

    const name = document.createElement("span");
    name.classList.add("todo-name");
    name.textContent = todoText;

    name.addEventListener("click", function () {
        li.classList.toggle("completed");
    });

    const buttons = document.createElement("div");
    buttons.classList.add("todo-buttons");

    const increaseButton = document.createElement("button");
    increaseButton.textContent = "+ Priority";
    increaseButton.classList.add("priority-up");

    increaseButton.addEventListener("click", function () {
        changePriority(li, 1);
    });

    const decreaseButton = document.createElement("button");
    decreaseButton.textContent = "- Priority";
    decreaseButton.classList.add("priority-down");

    decreaseButton.addEventListener("click", function () {
        changePriority(li, -1);
    });

    buttons.appendChild(increaseButton);
    buttons.appendChild(decreaseButton);
    li.appendChild(name);
    li.appendChild(buttons);
    todoList.appendChild(li);

    todoInput.value = "";
}

function changePriority(todo, direction) {
    let currentPriority = priorities.findIndex(function (priority) {
        return todo.classList.contains(priority);
    });

    let newPriority = currentPriority + direction;

    if (newPriority < 0 || newPriority >= priorities.length) {
        return;
    }

    todo.classList.remove(priorities[currentPriority]);
    todo.classList.add(priorities[newPriority]);
}

addButton.addEventListener("click", addTodo);

todoInput.addEventListener("keydown", function (event) {
    if (event.key === "Enter") {
        addTodo();
    }
});