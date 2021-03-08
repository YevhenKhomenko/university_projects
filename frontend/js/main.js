



var button = document.querySelector('.open-menu');
var showMenu = false;
var mobileMenu = document.querySelector('.nav-list-mobile');
var link = document.querySelectorAll(".nav-list-mobile li");
var closeMenu = document.querySelector('.close-menu');

button.onclick = function () {
    if(!showMenu){
        mobileMenu.style.display = "flex";
        showMenu = true;
    }
    else return false;
}

for (var i = 0; i < link.length; i++){
    link[i].onclick = function () {
        console.log(link[i])
        if(showMenu){
            mobileMenu.style.display = "none";
            showMenu = false;
        }
        else return false;
    }
}

closeMenu.onclick = function () {
    if(showMenu){
        mobileMenu.style.display = "none";
        showMenu = false;
    }
    else return false;
}

    let selectedItem = null
    let gallery = document.getElementsByClassName('game-gallery-desktop')[0]
    gallery.onclick = (event) => {
        let item = event.target.closest('.item'); if (!item) return
        if (selectedItem) {
           if (item.isSameNode(selectedItem)) {
              window.open(item.getElementsByClassName('gallery__img')[0].src)
           }
           let temp = selectedItem.innerHTML
           selectedItem.innerHTML = item.innerHTML
           item.innerHTML = temp
           selectedItem = null
        } else {
           selectedItem = item
        }
    }

function handleDragStart(e) {
    
    source = this;

  e.dataTransfer.effectAllowed = 'move';
  e.dataTransfer.setData('text', this.innerHTML);

}

function handleDragOver(e) {
    
  if (e.preventDefault) {
    e.preventDefault();
  }
  this.classList.add('over');

  return false;
}

function handleDragLeave(e) {
    
    this.classList.remove('over'); 

}

function handleDrop(e) {

  if (e.preventDefault) {
    e.preventDefault();

  }
    this.classList.remove('over');

    source.innerHTML = this.innerHTML;
    this.innerHTML = e.dataTransfer.getData('text');
  }

var fras = document.querySelectorAll('.item');
[].forEach.call(fras, function(fra) {
  fra.addEventListener('dragstart', handleDragStart, false);
  fra.addEventListener('dragover', handleDragOver, false);
  fra.addEventListener('dragleave', handleDragLeave, false);
  fra.addEventListener('drop', handleDrop, false);
});

/*function zoom(e){
  e.style.width = window.innerWidth;
  e.style.height = window.innerHeight;
}*/
