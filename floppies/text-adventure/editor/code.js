let current_game_data = {};

const set_current_game_data = (game_data) => {
  current_game_data = game_data;
};

const parse_file_data = (contents) => {
  try {
    const data_object = JSON.parse(contents);
    set_current_game_data(data_object);
    set_select_mode();
    console.log("Succesfully loaded game data.")
  } catch (parse_exception) {
    alert("The given data file is invalid!");
  }
};

const load_file = () => {
  console.log("Opening load dialogue.");

  const file_input = document.createElement("input");
  file_input.accept = '.json';
	file_input.type = 'file';
  file_input.style.display = 'none';
  
	file_input.onchange = (change_event) => {
		var file = change_event.target.files[0];
		if (!file) {
			return;
    }
    
		const reader = new FileReader();
		reader.onload = function(e) {
			const contents = e.target.result;
      parse_file_data(contents);
		}
		reader.readAsText(file);
  };

  file_input.click();
};

const save_file = () => {
  console.log("Opening save dialogue.");

  const download_element = document.createElement('a');
  const text = JSON.stringify(current_game_data, null, 2);
  download_element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text))
  download_element.setAttribute('download', 'game_data.json');
  download_element.style.display = 'none';
  download_element.click();
};

const clear_class = (class_name) => {
  let items = document.getElementsByClassName(class_name);
  for (let index=0; index < items.length; index++) {
    items[index].classList.remove(class_name);
  }
};

const insert_template = (target_id, template_id) => {
  const target = document.getElementById(target_id);
  if (target == null) {
    console.error("Target id " + target_id + " not found!");
    return;
  }
  const template = document.getElementById(template_id);
  if (template == null) {
    console.error("Template id " + template_id + " not found!");
    return;
  }
  target.innerHTML = template.innerHTML;
};

const set_element_visibility = (element_id, is_visible) => {
  const element = document.getElementById(element_id);
  if (element == null) {
    console.error("Could not find element with id " + element_id + "!");
    return;
  }

  if (is_visible) {
    element.style.display = 'inline-block';
  } else {
    element.style.display = 'none';
  }
};

const update_room_list = () => {
  const list_element = document.getElementById("room_list");
  const template = document.getElementById("room_item_template");
  for (let index = 0; index < current_game_data.rooms.length; index++) {
    const room_element = document.createElement("div");
    room_element.innerHTML = template.innerHTML;
    list_element.innerHTML += room_element.innerHTML;
  }
};

const set_add_room_mode = () => {
  console.log("Switching to add-room mode.");
  clear_class("selected");
  const add_room_button = document.getElementById("add_room");
  add_room_button.classList.add("selected");
  insert_template("inspector", "room_list_template");
  update_room_list();
  set_element_visibility('inspector', true);
};

const set_add_item_mode = () => {
  console.log("Switching to add-item mode.");
  clear_class("selected");
  const add_item_button = document.getElementById("add_item");
  add_item_button.classList.add("selected");
  insert_template("inspector", "item_list_template");
  set_element_visibility('inspector', true);
};

const set_add_npc_mode = () => {
  console.log("Switching to add-npc mode.");
  clear_class("selected");
  const add_npc_button = document.getElementById("add_npc");
  add_npc_button.classList.add("selected");
  insert_template("inspector", "npc_list_template");
  set_element_visibility('inspector', true);
};

const set_select_mode = () => {
  console.log("Switching to select mode.");
  clear_class("selected");
  const select_button = document.getElementById("select");
  select_button.classList.add("selected");
  set_element_visibility('inspector', false);
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
  set_add_room_mode();
};

// Start the app once the document has been loaded.
document.addEventListener('DOMContentLoaded', (event) => {
  main();
});
