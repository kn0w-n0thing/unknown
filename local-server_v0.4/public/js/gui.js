let config, updatedConfig;
let configPath = "assets/config.json";

//GUI variables
let mainColor;
let secondaryColor;
let thirdColor;
let connectColor;
let disconnectColor;
let guiBoxPosX, guiBoxPosY, guiSizeX, guiSizeY;
let marginX, marginY;
let requestButton;
let butSizeX, butSizeY;
let div;
let saveButton;
let terminal;
let isScrolledToBottom = false;
let font;
let fontSize;
let shutdownButton;

//SCREENS variables
let screenIdicatorColor = [];
let screenBoxColor = [];
let thumb = [];
let oscText = [];
let screenBoxSize, screenBoxSpacer;
let screenAddress = [];
let screenPort = [];
let singleDataLink = [];
let msgBox;
let isSaveMsgOn = false;
let isShutdownMsgOn = false;

//SOCKETS Variables
let localSocket;
let localServerAddress = "http://localhost:4000";
let remoteServerStatus = "disconnected";
let localServerStatus = "disconnected";
let runwaymlStatus = "disconnected";
let receivedData = "";

let requestTimer;
let autoRequestTimerInput;

// RUNWAY Image
let raw = new Image();
let imageCount = 0;

//system load data
let cpu;
let freeMem;
let totalMem;
let cpuGraphValues = [];
let memoryGraphValues = [];

function preload() {
  font = loadFont("assets/Roboto-Regular.ttf");
  loadGuiData();
}

function setup() {
  createCanvas(displayWidth, displayHeight);
  strokeWeight(2);

  //Pop-up message before reload page
  window.onbeforeunload = function () {
    return "";
  };

  guiBoxPosX = displayWidth / 100;
  guiBoxPosY = displayHeight / 50;
  guiSizeX = displayWidth / 2.5;
  guiSizeY = displayHeight / 3;

  screenBoxSize = guiSizeX / (config.screens.length + 1);
  screenBoxSpacer = screenBoxSize / (config.screens.length - 1.5);

  for (let i = 0; i < 20; i++) {
    cpuGraphValues.push(0);
    memoryGraphValues.push(0);
  }

  //SETUP FONT
  fontSize = 16;
  textFont(font);
  textSize(fontSize);
  textAlign(LEFT);

  //SETUP GUI ELEMENTS
  marginX = 10;
  marginY = 10;
  butSizeX = 110;
  butSizeY = 30;

  terminal = createElement("div");
  terminal.position(guiBoxPosX + marginX, guiBoxPosY + marginY);
  terminal.style("width", guiSizeX + "px");
  terminal.style("height", guiSizeY + "px");
  terminal.style("font-size", fontSize + "px");
  terminal.style("font-family", "Lucida Console, Courier, monospace");
  terminal.style("background-color", thirdColor);
  terminal.style("color", mainColor);
  terminal.style("border", "2px solid " + mainColor);
  terminal.style("overflow-y", "scroll");
  terminal.style("padding", "10px");
  terminal.style("scrollbar-color", mainColor + " " + secondaryColor);
  div = $("div");
  receivedData =
    "\n.##..##..##..##..##..##..##..##...####...##...##..##..##." +
    "\n.##..##..###.##..##.##...###.##..##..##..##...##..###.##." +
    "\n.##..##..##.###..####....##.###..##..##..##.#.##..##.###." +
    "\n.##..##..##..##..##.##...##..##..##..##..#######..##..##." +
    "\n..####...##..##..##..##..##..##...####....##.##...##..##.";
  receivedData +=
    "<br/><br/>For detailed instrctions on how to setup and run: <a href='https://github.com/fitosegrera/unknown' target='_blank'><strong>README</strong></a><br/>";
  receivedData +=
    "<br/>IMPORTANT: Please make sure all clients are up and running (remote-server, local-server, runwayml-(AI)). An indicator highlights the status of each client at any given time: green = connected, red = disconnected.<br/>";
  receivedData +=
    "<br/>Once all clients are connected a [START] button will appear on the bottom-right corner of this terminal.<br/>";
  terminal.html(receivedData);
  div.scrollTop(div[0].scrollHeight);

  requestButton = createButton("START");
  requestButton.style("font-size", fontSize + "px");
  requestButton.style("background-color", secondaryColor);
  requestButton.style("color", mainColor);
  requestButton.style("border", "2px solid " + mainColor);
  requestButton.size(butSizeX, butSizeY);
  requestButton.position(
    guiSizeX - butSizeX / 1.8,
    guiSizeY + butSizeY * 2 + marginY
  );
  requestButton.mousePressed(getRemoteData);
  requestButton.mouseOver(buttonHoverOn);
  requestButton.mouseOut(buttonHoverOut);
  requestButton.hide();

  for (let i = 0; i < config.screens.length; i++) {
    screenAddress.push(createInput(config.screens[i].ip, "text"));
    screenAddress[i].position(
      guiBoxPosX + marginX + (screenBoxSize + screenBoxSpacer) * i,
      guiSizeY + butSizeY * 9 + marginY * 1.5 + screenBoxSize
    );
    screenAddress[i].style("width", screenBoxSize - 10 + "px");
    screenAddress[i].style("background-color", thirdColor);
    screenAddress[i].style("color", mainColor);
    screenAddress[i].style("border-color", mainColor);

    screenPort.push(createInput(config.screens[i].port, "text"));
    screenPort[i].position(
      guiBoxPosX + marginX + (screenBoxSize + screenBoxSpacer) * i,
      guiSizeY + butSizeY * 10 + marginY * 1.5 + screenBoxSize
    );
    screenPort[i].style("width", screenBoxSize - 10 + "px");
    screenPort[i].style("background-color", thirdColor);
    screenPort[i].style("color", mainColor);
    screenPort[i].style("border-color", mainColor);
  }

  autoRequestTimerInput = createInput(config.requestTimer, "text");
  autoRequestTimerInput.style("width", screenBoxSize / 3 + "px");
  autoRequestTimerInput.style("height", butSizeY - 5 + "px");
  autoRequestTimerInput.position(
    guiSizeX / 2 + butSizeX * 2,
    guiSizeY + butSizeY * 2 + marginY
  );
  autoRequestTimerInput.style("background-color", thirdColor);
  autoRequestTimerInput.style("color", mainColor);
  autoRequestTimerInput.style("border-color", mainColor);

  saveButton = createButton("Save");
  saveButton.style("width", screenBoxSize / 2 + "px");
  saveButton.position(
    guiBoxPosX + marginX,
    guiSizeY + butSizeY * 11 + marginY * 4 + screenBoxSize
  );
  saveButton.style("background-color", thirdColor);
  saveButton.style("color", mainColor);
  saveButton.style("border-color", mainColor);
  saveButton.mouseOver(saveButtonHoverOn);
  saveButton.mouseOut(saveButtonHoverOut);
  saveButton.mousePressed(saveData);

  // newimg.attribute("width", guiSizeY + marginY * 2);
  // newimg.attribute("height", guiSizeY + marginY * 2);
  // newimg.style("border", "2px solid " + mainColor);
  // newimg.position(guiSizeX + marginX * 8, guiBoxPosY + marginY);

  shutdownButton = createButton("shutdown");
  shutdownButton.style("width", screenBoxSize / 1.5 + "px");
  shutdownButton.style("height", screenBoxSize / 4 + "px");
  shutdownButton.position(
    guiBoxPosX +
      marginX +
      (screenBoxSize + screenBoxSpacer) * config.screens.length +
      guiSizeY +
      marginY * 2 -
      screenBoxSize / 1.5,
    guiSizeY + butSizeY + marginY + screenBoxSize
  );
  shutdownButton.style("background-color", thirdColor);
  shutdownButton.style("color", mainColor);
  shutdownButton.style("border-color", mainColor);
  shutdownButton.mouseOver(shutdownButtonHoverOn);
  shutdownButton.mouseOut(shutdownButtonHoverOut);
  shutdownButton.mousePressed(shutdownMessage);

  ////////////////////////
  //Handle local sockets//
  ////////////////////////
  localSocket = io.connect(localServerAddress);
  localSocket.on("connect", () => {
    print("Local Server connected");
    localServerStatus = "connected";

    if (
      localServerStatus == "connected" &&
      remoteServerStatus == "connected" &&
      runwaymlStatus == "connected"
    ) {
      receivedData += "<br/>All clients connected!<br/>";
      receivedData += "When ready, please press [START]<br/>";
      terminal.html(receivedData);
      div.scrollTop(div[0].scrollHeight);
      setTimeout(() => {
        requestButton.show();
      }, 1000);
    } else {
      requestButton.hide();
    }
  });

  localSocket.on("disconnect", () => {
    localServerStatus = "disconnected";
    remoteServerStatus = "diconnected";
    receivedData += "<br/>ERROR: Connection with server lost!<br/>";
    receivedData +=
      "Please make sure both, the local and remote servers are running.<br/>";
    terminal.html(receivedData);
    div.scrollTop(div[0].scrollHeight);

    setTimeout(() => {
      requestButton.hide();
    }, 1000);

    for (let c = 0; c < screenIdicatorColor.length; c++) {
      screenIdicatorColor[c] = disconnectColor;
      thumb[c] = undefined;
      oscText[c] = "";
      if (singleDataLink[c] != undefined) {
        singleDataLink[c].remove();
      }
    }
  });

  localSocket.on("remote-status", (msg) => {
    remoteServerStatus = msg;
    print("Remote Server", remoteServerStatus);

    if (
      localServerStatus == "connected" &&
      remoteServerStatus == "connected" &&
      runwaymlStatus == "connected"
    ) {
      receivedData += "<br/>All clients connected!<br/>";
      receivedData += "When ready, please press [START]<br/>";
      terminal.html(receivedData);
      div.scrollTop(div[0].scrollHeight);
      setTimeout(() => {
        requestButton.show();
      }, 1000);
    } else {
      requestButton.hide();
    }
  });

  localSocket.on("headlines", (data) => {
    receivedData +=
      "<br/>Total headlines (zh): " +
      data.zh.articles.length +
      "<br/>Total headlines (en): " +
      data.en.articles.length +
      "<br/>";

    terminal.html(receivedData);
    div.scrollTop(div[0].scrollHeight);
  });

  localSocket.on("data-saved", (msg) => {
    receivedData += "<br/>Data saved as: " + msg + "<br/><br/>";
    terminal.html(receivedData);
    div.scrollTop(div[0].scrollHeight);
    imageCount = 0;
  });

  localSocket.on("image", (data) => {
    newDrawing(data.image);
    receivedData +=
      "(" + data.lang + ") image " + data.count + ".jpeg generated...<br/>";
    terminal.html(receivedData);
    div.scrollTop(div[0].scrollHeight);
  });

  localSocket.on("system-load", (sys) => {
    cpu = (sys.cpu * 100).toFixed();
    totalMem = (sys.totalMemory / 1000).toFixed(2);
    freeMem = totalMem - (sys.freeMemory / 1000).toFixed(2);
    cpuGraphValues.push(cpu);
    cpuGraphValues.shift();
    memoryGraphValues.push(freeMem);
    memoryGraphValues.shift();
  });

  localSocket.on("remote-error", (error) => {
    receivedData += "ERROR with service: " + error.type + "<br/>";
    receivedData += "ERROR: " + error.err + "<br/>";
    receivedData += "Please try again [START]...<br/>";
    terminal.html(receivedData);
    div.scrollTop(div[0].scrollHeight);

    if (
      localServerStatus == "connected" &&
      remoteServerStatus == "connected" &&
      runwaymlStatus == "connected"
    ) {
      receivedData += "<br/>All clients connected!<br/>";
      receivedData += "When ready, please press [START]<br/>";
      terminal.html(receivedData);
      div.scrollTop(div[0].scrollHeight);
      setTimeout(() => {
        requestButton.show();
      }, 1000);
    } else {
      requestButton.hide();
    }
  });

  localSocket.on("finished", (data) => {
    receivedData += "</br>(zh) images saved at: " + data.dataPaths.zh + "</br>";
    receivedData += "</br>(en) images saved at: " + data.dataPaths.en + "</br>";
    receivedData +=
      "</br>All processes finished with no errors!</br>Please see a record of downloaded headlines and images: <a href='http://localhost:4000/data.html' target='_blank'><strong>HERE</strong></a><br/>";
    receivedData +=
      "</br>An automatic data request will happen every " +
      requestTimer +
      " hours<br/>";
    receivedData +=
      "</br>If you wish to restart the process please refresh this page!<br/>";

    terminal.html(receivedData);
    div.scrollTop(div[0].scrollHeight);

    // setTimeout(() => {
    //   requestButton.show();
    // }, 1000);

    //request for new data every x time
    setInterval(() => {
      getRemoteData();
    }, requestTimer * 3.6e6);
  });

  // check for runwayml status at refresh
  localSocket.emit("runwayml-status");

  // receive runwayml status
  localSocket.on("runwayml-status", (status) => {
    if (status == "timeout") {
      receivedData +=
        "ERROR: runwayml connection timeout. Please check runwayml is setup and running...</br>";
      terminal.html(receivedData);
      div.scrollTop(div[0].scrollHeight);
    } else {
      runwaymlStatus = status;
      if (
        localServerStatus == "connected" &&
        remoteServerStatus == "connected" &&
        runwaymlStatus == "connected"
      ) {
        receivedData += "<br/>All clients connected!<br/>";
        receivedData += "When ready, please press [START]<br/>";
        terminal.html(receivedData);
        div.scrollTop(div[0].scrollHeight);
        setTimeout(() => {
          requestButton.show();
        }, 1000);
      } else {
        requestButton.hide();
      }
    }
  });

  // receive runwayml errors
  localSocket.on("runwayml-error", (err) => {});

  //SCREENS communication events
  for (let c = 0; c < config.screens.length; c++) {
    //SCREENS status
    localSocket.on("screen-status-" + (c + 1), (data) => {
      if (data) {
        screenIdicatorColor[c] = connectColor;
      } else {
        screenIdicatorColor[c] = disconnectColor;
        thumb[c] = undefined;
        oscText[c] = "";

        if (singleDataLink[c] != undefined) {
          singleDataLink[c].remove();
        }
      }
    });

    //SCREENS IP MISMATCH
    localSocket.on("screen-ip-mismatch", (msg) => {
      oscText[msg.id] =
        "ERROR: IP mismatch\nYou: " +
        config.screens[msg.id].ip +
        "\nGot: " +
        msg.ip;
    });

    //SCREENS request data "READY"
    localSocket.on("screen-ready-" + (c + 1), (data) => {
      let a = data.article;
      // console.log(a);
      let lang = data.language;
      let translation;
      if (lang == "zh") {
        translation = a.translation;
      } else {
        translation = a.title;
      }

      if (thumb[c] != undefined) {
        thumb[c].remove();
      }
      thumb[c] = createImg(data.image);
      thumb[c].hide();

      oscText[c] = "Headline and\nimage sent!";

      if (singleDataLink[c] != undefined) {
        singleDataLink[c].remove();
      }

      setTimeout(() => {
        oscText[c] = "";
        singleDataLink[
          c
        ] = createA(
          "http://localhost:4000/single.html?headline='" +
            a.title +
            "&translation=" +
            translation +
            "&imgurl=" +
            data.image +
            "&url=" +
            a.url +
            "&author=" +
            a.author +
            "&published=" +
            a.publishedAt,
          "MORE INFO",
          ["_blank"]
        );
        singleDataLink[c].position(
          marginX * 3 + c * (screenBoxSize + screenBoxSpacer),
          guiSizeY + butSizeY * 7 + marginY + screenBoxSize
        );
        singleDataLink[c].style("font-weight", "bold");
      }, 3000);
    });
  }
}

function draw() {
  background(secondaryColor);
  noStroke();

  let tmpColorRemote, tmpColorLocal, tmpColorRunway;
  let indicatorSize = 10;

  if (remoteServerStatus == "connected") {
    tmpColorRemote = connectColor;
  } else {
    tmpColorRemote = disconnectColor;
  }

  if (localServerStatus == "connected") {
    tmpColorLocal = connectColor;
  } else {
    tmpColorLocal = disconnectColor;
  }

  if (runwaymlStatus == "connected") {
    tmpColorRunway = connectColor;
  } else {
    tmpColorRunway = disconnectColor;
  }

  //draw images frame
  stroke(mainColor);
  fill(thirdColor);
  rect(
    guiSizeX + marginX * 8 - 7,
    guiBoxPosY + marginY - 7,
    guiSizeY + marginY * 2,
    guiSizeY + marginY * 2
  );
  noStroke();

  //draw status for local server
  fill(tmpColorLocal);
  ellipse(
    guiBoxPosX + indicatorSize,
    guiBoxPosY - indicatorSize,
    indicatorSize,
    indicatorSize
  );
  fill(mainColor);
  text(
    "local-server: " + localServerStatus,
    indicatorSize * 2.5 + guiBoxPosX,
    guiBoxPosY - fontSize / 3
  );

  //draw status for remote server
  fill(tmpColorRemote);
  ellipse(
    guiBoxPosX + guiSizeX / 3 + indicatorSize / 2,
    guiBoxPosY - indicatorSize,
    indicatorSize,
    indicatorSize
  );
  fill(mainColor);
  text(
    "remote-server: " + localServerStatus,
    indicatorSize * 2 + guiBoxPosX + guiSizeX / 3,
    guiBoxPosY - fontSize / 3
  );

  //draw status for runwayml
  fill(tmpColorRunway);
  ellipse(
    guiBoxPosX + (guiSizeX - guiSizeX / 3) + indicatorSize / 2,
    guiBoxPosY - indicatorSize,
    indicatorSize,
    indicatorSize
  );
  fill(mainColor);
  text(
    "runwayml-(AI): " + runwaymlStatus,
    indicatorSize * 2 + guiBoxPosX + (guiSizeX - guiSizeX / 3),
    guiBoxPosY - fontSize / 3
  );

  //cpu graph
  let x1 = marginX * 2;
  let y1 = guiSizeY + butSizeY + marginY * 6;
  let maxVal = 30;
  let graphSpacer = screenBoxSize / cpuGraphValues.length;
  fill(thirdColor);
  rect(x1, y1 - maxVal, graphSpacer * cpuGraphValues.length, maxVal + 5);
  stroke(mainColor);
  for (let i = 0; i < cpuGraphValues.length; i++) {
    if (i > 0) {
      line(
        x1 + i * graphSpacer,
        y1 - map(cpuGraphValues[i], 0, 100, 0, maxVal),
        x1 + (i - 1) * graphSpacer,
        y1 - map(cpuGraphValues[i - 1], 0, 100, 0, maxVal)
      );
      line(
        x1 + i * graphSpacer,
        y1 - map(memoryGraphValues[i], 0, totalMem, 0, maxVal),
        x1 + (i - 1) * graphSpacer,
        y1 - map(memoryGraphValues[i - 1], 0, totalMem, 0, maxVal)
      );
    }
  }

  //cpu + memory text
  fill(mainColor);
  noStroke();
  text(
    "CPU: " + cpu + " %",
    marginX * 3 + graphSpacer * cpuGraphValues.length,
    guiSizeY + butSizeY * 2 + marginY * 1.5
  );
  text(
    "MEM: " + freeMem + " / " + totalMem + " GB",
    marginX * 3 + graphSpacer * cpuGraphValues.length,
    guiSizeY + butSizeY * 2 + marginY * 1.5 + fontSize
  );

  text(
    "Auto-request time (hrs):",
    guiSizeX / 3 + butSizeX * 1.4,
    guiSizeY + butSizeY * 2 + marginY * 2.2
  );

  //screen clients indicators
  for (let i = 0; i < config.screens.length; i++) {
    stroke(mainColor);
    fill(screenBoxColor[i]);
    rect(
      marginX * 2 + i * (screenBoxSize + screenBoxSpacer),
      guiSizeY + butSizeY * 5 + marginY,
      screenBoxSize,
      screenBoxSize
    );
    if (thumb[i] != undefined) {
      image(
        thumb[i],
        marginX * 2 + i * (screenBoxSize + screenBoxSpacer),
        guiSizeY + butSizeY * 5 + marginY,
        screenBoxSize,
        screenBoxSize
      );
    }
    noStroke();
    fill(screenIdicatorColor[i]);
    ellipse(
      indicatorSize / 2 + marginX * 2 + i * (screenBoxSize + screenBoxSpacer),
      guiSizeY + butSizeY * 6 + marginY + screenBoxSize - indicatorSize / 2,
      indicatorSize
    );
    fill(mainColor);
    text(
      "Screen " + config.screens[i].id,
      indicatorSize * 2 + marginX * 2 + i * (screenBoxSize + screenBoxSpacer),
      guiSizeY + butSizeY * 6 + marginY + screenBoxSize
    );
    text(
      oscText[i],
      marginX * 2 + i * (screenBoxSize + screenBoxSpacer),
      guiSizeY + butSizeY * 7 + marginY + screenBoxSize
    );
  }
}

//send message to local server to get headlines and translations
function getRemoteData() {
  receivedData += "</br>-------------------------------------<br/>";
  receivedData +=
    "</br>Requesting data from Remote Server...<br/>Please wait...<br/>";

  terminal.html(receivedData);
  div.scrollTop(div[0].scrollHeight);

  localSocket.emit("get-remote-data");
  requestButton.hide();
}

function buttonHoverOn() {
  requestButton.style("background-color", mainColor);
  requestButton.style("color", secondaryColor);
}

function buttonHoverOut() {
  requestButton.style("background-color", secondaryColor);
  requestButton.style("color", mainColor);
}

function saveButtonHoverOn() {
  saveButton.style("background-color", mainColor);
  saveButton.style("color", secondaryColor);
}

function saveButtonHoverOut() {
  saveButton.style("background-color", secondaryColor);
  saveButton.style("color", mainColor);
}

function shutdownButtonHoverOn() {
  shutdownButton.style("background-color", mainColor);
  shutdownButton.style("color", secondaryColor);
}

function shutdownButtonHoverOut() {
  shutdownButton.style("background-color", secondaryColor);
  shutdownButton.style("color", mainColor);
}

function okButtonHoverOn() {
  msgBox.okButton.style("background-color", mainColor);
  msgBox.okButton.style("color", secondaryColor);
}

function okButtonHoverOut() {
  msgBox.okButton.style("background-color", secondaryColor);
  msgBox.okButton.style("color", mainColor);
}

function cancelButtonHoverOn() {
  msgBox.cancelButton.style("background-color", mainColor);
  msgBox.cancelButton.style("color", secondaryColor);
}

function cancelButtonHoverOut() {
  msgBox.cancelButton.style("background-color", secondaryColor);
  msgBox.cancelButton.style("color", mainColor);
}

function cancelSave() {
  msgBox.destroy();
}

function saveData() {
  isSaveMsgOn = true;
  msgBox = new MessageBox(
    "save",
    "Are you sure you want to save all changes?",
    secondaryColor,
    mainColor,
    width / 2 - 200,
    300,
    400,
    200
  );
  msgBox.okButton.mouseOver(okButtonHoverOn);
  msgBox.okButton.mouseOut(okButtonHoverOut);
  msgBox.okButton.mousePressed(saveConfigData);
  msgBox.cancelButton.mouseOver(cancelButtonHoverOn);
  msgBox.cancelButton.mouseOut(cancelButtonHoverOut);
  msgBox.cancelButton.mousePressed(cancelSave);
}

function shutdownMessage() {
  isShutdownMsgOn = true;
  msgBox = new MessageBox(
    "shutdown",
    "This operation will shutdown all " +
      config.screens.length +
      " News Headlines PCs. Are you sure you want to continue?",
    secondaryColor,
    mainColor,
    width / 2 - 200,
    300,
    400,
    200
  );
  msgBox.okButton.mouseOver(okButtonHoverOn);
  msgBox.okButton.mouseOut(okButtonHoverOut);
  msgBox.okButton.mousePressed(shutDown);
  msgBox.cancelButton.mouseOver(cancelButtonHoverOn);
  msgBox.cancelButton.mouseOut(cancelButtonHoverOut);
  msgBox.cancelButton.mousePressed(cancelshutDown);
}

function shutDown() {
  print("shutdown PCs...");
  localSocket.emit("shutdown");
  msgBox.destroy();
}

function cancelshutDown() {
  msgBox.destroy();
}

//save changes to configuration file
async function saveConfigData() {
  let i = 0;
  await config.screens.forEach((screen) => {
    updatedConfig.screens[i].ip = screenAddress[i].value();
    updatedConfig.screens[i].port = screenPort[i].value();
    i++;
  });

  updatedConfig.requestTimer = autoRequestTimerInput.value();
  localSocket.emit("save-config", updatedConfig);
  msgBox.destroy();
}

function newDrawing(data) {
  //get the results form Runway
  //if there is data with a key of result
  //create an image
  if (data && data.result) {
    newimg = createImg(data.result);
    newimg.attribute("width", guiSizeY + marginY * 2);
    newimg.attribute("height", guiSizeY + marginY * 2);
    newimg.style("border", "2px solid " + mainColor);
    newimg.position(guiSizeX + marginX * 8, guiBoxPosY + marginY);
  }
}

function loadGuiData() {
  config = loadJSON(configPath, () => {
    //console.log(config);
    config = config.gui;
    mainColor = config.mainColor;
    secondaryColor = config.secondaryColor;
    thirdColor = config.thirdColor;
    connectColor = config.connectColor;
    disconnectColor = config.disconnectColor;
    updatedConfig = config;
    requestTimer = config.requestTimer;
    config.screens.forEach((element) => {
      screenIdicatorColor.push(disconnectColor);
      screenBoxColor.push(thirdColor);
      oscText.push("");
    });
    thumb = new Array(config.screens.length);
    singleDataLink = new Array(config.screens.length);
  });
}

function keyPressed() {
  if (isSaveMsgOn) {
    if (keyCode == 27) {
      //ESCAPE
      msgBox.destroy();
      isSaveMsgOn = false;
    }
    if (keyCode == 13) {
      //ENTER
      saveConfigData();
      isSaveMsgOn = false;
    }
  }
  if (isShutdownMsgOn) {
    if (keyCode == 27) {
      //ESCAPE
      msgBox.destroy();
      isShutdownMsgOn = false;
    }
    if (keyCode == 13) {
      //ENTER
      shutDown();
      isShutdownMsgOn = false;
    }
  }
}
