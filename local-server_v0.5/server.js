//Configuration File
const configPath = "./public/assets/config.json";
const config = require(configPath);

//file system
const fs = require("fs");

//cpu % usage
const os = require("os-utils");

//EXPRESS Server
const express = require("express");
const app = express();
const port = config.server.port;
app.use(express.static("public"));

//Web Sockets. Local & Remote
const http = require("http").createServer(app);
const io_server = require("socket.io")(http); // socket.io server
const io_client = require("socket.io-client");

//OSC
const { Server, Client } = require("node-osc");
const { Console } = require("console");
const oscHost = config.oscReceiver.host;
const oscPort = config.oscReceiver.port;

//NewsAPI
let headlines = {};
let remoteServer = config.remoteServer.url;
let remoteServerStatus = "disconnected";

//Headlines Json file
let headlinesJsonPath = __dirname + config.data.headlinesJson;

//Chinese DATA folder
let zhFolderPath = config.data.zhFolder;
let zhImageServerPath = __dirname + zhFolderPath;

//English DATA folder
let enFolderPath = config.data.enFolder;
let enImageServerPath = __dirname + enFolderPath;

//File cue (count)
let cue = config.cue;
let tmpCue = 0;

//RUNWAYML
let runwaySocketUrl = config.runwayml.url;
let runwaySocket;
let imageCount = 0;
let debug = config.debug;
let langIsZh = true;
let tmpPath = "";
let runwaymlReady = false;
let runwaymlStatus = "disconnected";
let runwayTimeout;

///////////////////////
//CHECK AND RESET CUE//
///////////////////////
function resetCue() {
  let rawConfig = fs.readFileSync(configPath);
  tmpConfig = JSON.parse(rawConfig);
  cue = tmpConfig.cue;

  if (cue % 20 != 0) {
    if ((cue >= 0 && cue <= 9) || (cue >= 50 && cue <= 59)) {
      cue = 0;
    } else if (cue >= 10 && cue <= 29) {
      cue = 20;
    } else if (cue >= 30 && cue <= 49) {
      cue = 40;
    }
    config.cue = cue;
    saveJsonData(config, configPath, (res) => {
      if (debug) {
        console.log("CUE:", cue);
        console.log(res);
      }
    });
  }
}

/////////////
//SETUP OSC//
/////////////
const oscReceiver = new Server(oscPort, oscHost, () => {
  if (debug) {
    console.log("OSC receiver is listening on", oscHost, oscPort);
  }
});

let oscClients = new Array(config.gui.screens.length);
let pingTimeout = new Array(config.gui.screens.length);

for (let c = 0; c < oscClients.length; c++) {
  oscClients[c] = new Client(
    config.gui.screens[c].ip,
    parseInt(config.gui.screens[c].port)
  );
}

if (debug) {
  console.log(config);
}

///////////////////
//Handle OSC data//
///////////////////
for (let c = 0; c < oscClients.length; c++) {
  oscReceiver.on("/screen" + (c + 1), (msg, cli) => {
    if (msg[1] == "ping") {
      //console.log(msg);
      io_server.emit("screen-status-" + (c + 1), true);
      clearTimeout(pingTimeout[c]);
      pingTimeout[c] = setTimeout(() => {
        if (debug) {
          console.log("screen", c + 1, "offline!");
        }
        io_server.emit("screen-status-" + (c + 1), false);
      }, config.gui.ping * 2);
    }
    if (msg[1] == "ready") {
      if (cli.address == config.gui.screens[c].ip) {
        let rawJson = fs.readFileSync(headlinesJsonPath);
        let parsedJson = JSON.parse(rawJson);
        let lang;
        let articles;
        if (msg[2] == "zh") {
          lang = "zh";
          articles = parsedJson.zh.articles;
        } else {
          lang = "en";
          articles = parsedJson.en.articles;
        }

        let randHedlineIndex = Math.floor(
          Math.random() * parsedJson.zh.articles.length
        );

        let headline = articles[randHedlineIndex].title;
        let imgUrl =
          ":" + port + "/data/" + msg[2] + "/" + randHedlineIndex + ".jpeg";
        oscClients[c].send("/headline-" + (c + 1), headline, imgUrl);
        //console.log(articles[randHedlineIndex]);
        io_server.emit("screen-ready-" + (c + 1), {
          article: articles[randHedlineIndex],
          image: "/data/" + msg[2] + "/" + randHedlineIndex + ".jpeg",
          language: lang,
        });
        if (debug) {
          console.log("Screen ", c, headline, imgUrl);
          console.log("random Hedline Index:", randHedlineIndex);
        }
      } else {
        io_server.emit("screen-ip-mismatch", { id: c, ip: cli.address });
      }
    }
  });
}

////////////
//PING OSC//
////////////
setInterval(() => {
  for (let c = 0; c < oscClients.length; c++) {
    oscClients[c].send("/ping" + (c + 1));
  }
}, config.gui.ping);

//////////////////////
//Save Data Function//
//////////////////////
//save received data into Json File
function saveJsonData(totalData, path, res) {
  let obj = JSON.stringify(totalData, null, 4);

  fs.writeFile(path, obj, (error) => {
    if (error) {
      res(error);
    } else {
      res("json file saved as " + path);
    }
  });
}

///////////////////////////////
//Handle local server sockets//
///////////////////////////////
//Data transmission between local server with ai, screens and starmap
io_server.on("connection", (socket) => {
  resetCue();

  if (debug) {
    console.log("We have a new LOCAL client: " + socket.id);
  }

  socket.emit("remote-status", remoteServerStatus);

  socket.on("disconnect", () => {
    if (debug) {
      console.log("Client has disconnected");
    }
  });

  //When local server requests data
  socket.on("get-remote-data", () => {
    runwaymlReady = true;
    getRemoteData();
    if (debug) {
      console.log("requesting remote data...");
    }
  });

  //When headlines.html requests data
  socket.on("get-local-data", () => {
    let rawData = fs.readFileSync(headlinesJsonPath);
    let tmpJsonHeadlines = JSON.parse(rawData);
    socket.emit("result-local-data", {
      headlines: tmpJsonHeadlines,
    });
  });

  //When headlines.html requests data
  socket.on("save-config", (data) => {
    //console.log(data);
    config.gui = data;
    saveJsonData(config, configPath, (res) => {
      if (debug) {
        console.log(res);
      }
      socket.emit("data-saved", configPath);

      //close all OSC clients and reconnect
      for (let c = 0; c < oscClients.length; c++) {
        oscClients[c].close();
        oscClients[c] = new Client(
          data.screens[c].ip,
          parseInt(data.screens[c].port)
        );
      }
    });
  });

  socket.on("runwayml-status", () => {
    socket.emit("runwayml-status", runwaymlStatus);
  });

  socket.on("shutdown", () => {
    for (let c = 0; c < oscClients.length; c++) {
      oscClients[c].send("/shutdown" + (c + 1));
    }
  });
});

/////////////////////////
//Handle Remote sockets//
/////////////////////////
//Data transmission back and forth with server in Hong Kong
let remoteSocket = io_client.connect(remoteServer);

remoteSocket.on("connect", () => {
  if (debug) {
    console.log("connected to remote server:", remoteServer);
  }
  remoteServerStatus = "connected";
  io_server.emit("remote-status", remoteServerStatus);
});

remoteSocket.on("result", (res) => {
  io_server.emit("headlines", res);
  headlines = res;
  if (debug) {
    console.log("=====================");
    console.log(headlines);
  }

  txtToImg = headlines.zh.articles[imageCount].translation;

  if (debug) {
    console.log("zh RENDERING IMAGE", imageCount);
  }

  let rawJson = fs.readFileSync(headlinesJsonPath);
  let parsedJson = JSON.parse(rawJson);

  let zhCueCount = 0;
  headlines.zh.articles.forEach((h) => {
    parsedJson.zh.articles[cue + zhCueCount] = h; //cue + zhCueCount;
    zhCueCount++;
  });

  let enCueCount = 0;
  headlines.en.articles.forEach((h) => {
    parsedJson.en.articles[cue + enCueCount] = h; //cue + enCueCount;
    enCueCount++;
  });

  console.log(parsedJson);

  saveJsonData(parsedJson, headlinesJsonPath, (res) => {
    if (debug) {
      console.log(res);
    }
    io_server.emit("data-saved", headlinesJsonPath);
    getAi(txtToImg);
    runwayConnectionTimeout();
  });
});

remoteSocket.on("error", (error) => {
  if (debug) {
    console.log("=====================");
    console.error("ERROR with service", error.type);
    console.error("ERROR ", error.err);
    console.error("Please try again.");
    io_server.emit("remote-error", error);
  }
});

////////////////////////////
//Handle Runway ML sockets//
////////////////////////////
//setup communication with Runway ML
runwaySocket = io_client.connect(runwaySocketUrl);

//on connection
runwaySocket.on("connect", () => {
  if (debug) {
    console.log("runwayml connected!");
  }
  runwaymlStatus = "connected";
  io_server.emit("runwayml-status", runwaymlStatus);
  runwaymlReady = true;
});

//on disconnection
runwaySocket.on("disconnect", () => {
  if (debug) {
    console.log("runwayml disconnected!");
  }
  runwaymlStatus = "disconnected";
  io_server.emit("runwayml-status", runwaymlStatus);
  runwaymlReady = false;
});

//On receiving image data
runwaySocket.on("data", (img) => {
  //console.log(img);
  clearTimeout(runwayTimeout);

  let data = img.result;
  let imgData = data.replace(/^data:image\/\w+;base64,/, "");
  let buf = new Buffer(imgData, "base64");

  let tmpLang;
  let tmpTotalArticles;
  let tmpArticles;

  if (langIsZh) {
    tmpPath = zhImageServerPath;
    tmpLang = "zh";
    if (headlines.zh != undefined) {
      tmpTotalArticles = headlines.zh.articles.length;
      tmpArticles = headlines.zh.articles;
    }
  } else {
    tmpPath = enImageServerPath;
    tmpLang = "en";
    if (headlines.en != undefined) {
      tmpTotalArticles = headlines.en.articles.length;
      tmpArticles = headlines.en.articles;
    }
  }

  if (runwaymlReady && tmpArticles != undefined) {
    //Save images to disk
    let imgFileToSave = tmpPath + (cue + imageCount - 1) + ".jpeg";

    fs.writeFile(imgFileToSave, buf, (err) => {
      if (debug) {
        console.log("Is language zh?", langIsZh);
        console.log("image saved...", imgFileToSave);
      }

      io_server.emit("image", { lang: tmpLang, image: img, count: imageCount });
      if (err) throw err;
      //Repeat the getAi() function untill all headlines
      //have been converted to images
      getImagesRecursive(tmpLang, tmpTotalArticles, tmpArticles);
    });
  } else {
    runwaymlReady = true;
  }
});

//On receiving Error
runwaySocket.on("error", (err) => {
  io_server.emit("runwayml-error", err);
  if (debug) {
    console.log(err);
  }
});

//On receiving INFO
if (debug) {
  runwaySocket.on("info", (info) => {
    if (debug) {
      console.log(info);
    }
  });
}

///////////////////////////////////
//Get News Data fromRemote Server//
///////////////////////////////////
function getRemoteData() {
  headlines = {};
  remoteSocket.emit("getData");
}

/////////////////////////////////////////
//Send the text to Runway via Socket.io//
/////////////////////////////////////////
function getAi(cap) {
  // console.log("original", cap);
  let capsToSend = cap.replace(/\(.+?\)/g, "");
  capsToSend = capsToSend.replace(/[^a-z0-9+]+/gi, " ");
  capsToSend = capsToSend.toLowerCase();
  //console.log(capsToSend);
  let postData = { caption: capsToSend };
  runwaySocket.emit("query", postData);
  //console.log("image count:", imageCount);
  imageCount++;
}

////////////////////////////////
//Get all images from runwayml//
////////////////////////////////
function getImagesRecursive(lang, imgNum, articles) {
  if (imageCount < imgNum) {
    let txtToImg = articles[imageCount].translation;
    if (debug) {
      console.log(lang, "RENDERING IMAGE", imageCount);
    }
    getAi(txtToImg);
  } else {
    tmpCue += imageCount;
    imageCount = 0;
    if (debug) {
      console.log(lang, "RENDERING IMAGES DONE", "image-count:", imageCount);
    }
    if (langIsZh) {
      langIsZh = false;
      getAi(headlines.en.articles[imageCount].translation);
    } else {
      io_server.emit("finished", {
        dataPaths: { zh: zhImageServerPath, en: enImageServerPath },
      });
      langIsZh = true;
      runwaymlReady = false;
      cue += tmpCue /= 2;
      tmpCue = 0;
      if (cue >= 60) {
        cue = 0;
      }
      config.cue = cue;
      saveJsonData(config, configPath, (res) => {
        if (debug) {
          console.log("CUE:", cue);
          console.log(res);
        }
      });
    }
  }
}

/////////////////////////////
//Runway Connection Timeout//
/////////////////////////////
function runwayConnectionTimeout() {
  if (debug) {
    console.log("runwayml connection timeout started");
  }
  runwayTimeout = setTimeout(() => {
    io_server.emit("runwayml-status", "timeout");
    if (debug) {
      console.log(
        "runwayml connection timeout distroyed",
        runwayTimeout._destroyed
      );
    }
  }, 10000);
}

/////////
//CPU %//
/////////
setInterval(() => {
  let sysData = { cpu: 0, freeMemory: 0, totalMemory: 0 };
  os.cpuUsage((v) => {
    sysData.cpu = v;
    sysData.freeMemory = os.freemem();
    sysData.totalMemory = os.totalmem();
    io_server.emit("system-load", sysData);
  });
}, 500);

//////////////////////
//Run Express Server//
//////////////////////
http.listen(port, () => {
  if (debug) {
    console.log("App listening at http://localhost:" + port);
  }
});
