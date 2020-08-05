class MessageBox {
  constructor(label, message, bg, c, x, y, w, h) {
    this.label = label;
    this.message = message;
    this.bg = bg;
    this.c = c;
    this.fontSize = 16;

    this.box = createElement("div");
    this.box.style("background-color", this.bg);
    this.box.style("border", "2px solid " + this.c);
    this.box.style("z-index", "2");
    this.box.style("color", this.c);
    this.box.style("width", w + "px");
    this.box.style("height", h + "px");
    this.box.position(x, y);
    this.box.style("font-size", "24px");
    this.box.style("font-family", "Lucida Console, Courier, monospace");
    this.box.style("box-shadow", "10px 15px 20px #111111");
    this.box.attribute("draggable", "true");

    this.bar = createElement("div");
    this.bar.style("background-color", this.c);
    this.bar.style("z-index", "10");
    this.bar.style("color", this.bg);
    this.bar.style("width", w + "px");
    this.bar.style("height", h / 7 + "px");
    this.bar.style("font-size", "20px");
    this.bar.style("margin-top", "0px");
    this.bar.style("font-weight", "bold");
    this.bar.style("text-align", "left");
    this.bar.style("font-family", "Lucida Console, Courier, monospace");
    this.bar.style("position", "absolute");

    this.barMsg = createP(this.label);
    this.barMsg.style("position", "relative");
    this.barMsg.style("color", this.bg);
    this.barMsg.style("margin-top", "0px");
    this.barMsg.style("padding-left", "10px");
    this.barMsg.style("z-index", "12");
    this.barMsg.style("display", "inline");
    this.boxMsg = createP(this.message);
    this.boxMsg.style("position", "relative");
    this.boxMsg.style("color", this.c);
    this.boxMsg.style("font-size", this.fontSize + "px");
    this.boxMsg.style("margin-top", h / 4 + "px");
    this.boxMsg.style("padding-left", "20px");
    this.boxMsg.style("z-index", "13");

    let butWidth = 70;
    let butHeight = 30;
    this.okButton = createButton("ok");
    this.okButton.style("font-size", this.fontSize + "px");
    this.okButton.style("background-color", this.bg);
    this.okButton.style("color", this.c);
    this.okButton.style("border", "2px solid " + this.c);
    this.okButton.style("position", "relative");
    this.okButton.size(butWidth, butHeight);
    this.okButton.position(w - butWidth * 1.2, h - butHeight * 1.5);

    this.cancelButton = createButton("cancel");
    this.cancelButton.style("font-size", this.fontSize + "px");
    this.cancelButton.style("background-color", this.bg);
    this.cancelButton.style("color", this.c);
    this.cancelButton.style("border", "2px solid " + this.c);
    this.cancelButton.style("position", "relative");
    this.cancelButton.size(butWidth, butHeight);
    this.cancelButton.position(w - butWidth * 2.5, h - butHeight * 1.5);

    this.barMsg.parent(this.bar);
    this.bar.parent(this.box);
    this.boxMsg.parent(this.box);
    this.cancelButton.parent(this.bar);
    this.okButton.parent(this.bar);
  }

  destroy() {
    this.box.remove();
    this.bar.remove();
    this.barMsg.remove();
    this.boxMsg.remove();
    this.okButton.remove();
  }
}
