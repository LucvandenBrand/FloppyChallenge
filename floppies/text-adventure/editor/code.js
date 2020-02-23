let current_game_data = {};

const set_current_game_data = (game_data) => {
  current_game_data = game_data;
}

const parse_file_data = (contents) => {
  try {
    const data_object = JSON.parse(contents);
    set_current_game_data(data_object);
    console.log("Succesfully loaded game data.")
  } catch (parse_exception) {
    alert("The given data file is invalid!");
  }
};

const load_file = () => {
  console.log("Opening load dialogue.");

  file_input = document.createElement("input");
  file_input.accept = '.json';
	file_input.type = 'file';
  file_input.style.display = 'none';
  
	file_input.onchange = (change_event) => {
		var file = change_event.target.files[0];
		if (!file) {
			return;
    }
    
		var reader = new FileReader();
		reader.onload = function(e) {
			var contents = e.target.result;
      parse_file_data(contents);
		}
		reader.readAsText(file);
  };

  file_input.click();
};

const save_file = () => {
  console.log("Opening save dialogue.");
};

const clear_class = (class_name) => {
  let items = document.getElementsByClassName(class_name);
  for (let index=0; index < items.length; index++) {
    items[index].classList.remove(class_name);
  }
}

const set_add_room_mode = () => {
  console.log("Switching to add-room mode.");
  clear_class("selected");
  const add_room_button = document.getElementById("add_room");
  add_room_button.classList.add("selected");
};

const set_add_item_mode = () => {
  console.log("Switching to add-item mode.");
  clear_class("selected");
  const add_item_button = document.getElementById("add_item");
  add_item_button.classList.add("selected");
};

const set_add_npc_mode = () => {
  console.log("Switching to add-npc mode.");
  clear_class("selected");
  const add_npc_button = document.getElementById("add_npc");
  add_npc_button.classList.add("selected");
};

const set_select_mode = () => {
  console.log("Switching to select mode.");
  clear_class("selected");
  const select_button = document.getElementById("select");
  select_button.classList.add("selected");
};

const setup_buttons = () => {
  const load_button = document.getElementById("load");
  load_button.addEventListener("click", load_file);

  const save_button = document.getElementById("save");
  save_button.addEventListener("click", save_file);

  const add_room_button = document.getElementById("add_room");
  add_room_button.addEventListener("click", set_add_room_mode);

  const add_item_button = document.getElementById("add_item");
  add_item_button.addEventListener("click", set_add_item_mode);

  const add_npc_button = document.getElementById("add_npc");
  add_npc_button.addEventListener("click", set_add_npc_mode);

  const select_button = document.getElementById("select");
  select_button.addEventListener("click", set_select_mode);
};

const resize = () => {
  const canvas = document.getElementById("canvas");
  const rect = canvas.parentNode.getBoundingClientRect();
  canvas.width = rect.width;
  canvas.height = rect.height;
};

const main = () => {
  console.log("Story Editor Started.");

  resize();
  window.addEventListener("resize", resize);

  setup_buttons();
};

// Start the app once the document has been loaded.
document.addEventListener('DOMContentLoaded', (event) => {
  main();
});
