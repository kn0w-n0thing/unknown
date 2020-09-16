const config = require("./config");
const fetch = require("node-fetch"); //Configuration File
const AWS = require("aws-sdk"); //Amazon Translate
const express = require("express");
const app = express();
const port = config.server.port;
var http = require("http").createServer(app);
var io = require("socket.io")(http);

app.use(express.static("public"));

let translate = new AWS.Translate({
  accessKeyId: config.aws.accessKeyId,
  secretAccessKey: config.aws.secretAccessKey,
  region: config.aws.region,
});

let newsApiKey = "cbe6c777df4645fcaeab1bc46828055f";

let headlinesData = { zh: {}, en: {} };

//Async translation function
async function translateData(headlines, res) {
  let toBeTrasnlated = "";
  let separator = "\n\n";

  console.log("headlines", headlines.zh.articles.length);
  await headlines.zh.articles.forEach((article) => {
    toBeTrasnlated += article.title + separator;
    //console.log("ORIGINAL ARTICLE", article.title);
  });

  let translateOpts = {
    SourceLanguageCode: "auto",
    TargetLanguageCode: "en",
    Text: toBeTrasnlated,
  };

  translate.translateText(translateOpts, (err, data) => {
    let splitted = data.TranslatedText.split(separator);
    splitted.pop();
    console.log("splitted", splitted.length);
    for (let i = 0; i < splitted.length; i++) {
      //console.log("TRANSLATED ARTICLE", i, splitted[i].trimStart());
      headlinesData.zh.articles[i].translation = splitted[i].trimStart();
      headlinesData.en.articles[i].translation =
        headlinesData.en.articles[i].title;
    }
    res(headlinesData);
  });
}

async function main(res) {
  console.log("request received, fetching data...");
  //Chinese News Fetch
  let country = "cn";
  let newsResponse = await fetch(
    "https://newsapi.org/v2/top-headlines?country=" +
      country +
      "&apiKey=" +
      newsApiKey
  ).catch((err) => {
    console.error(err);
    io.emit("error", { type: "newsapi.org", err: err });
  });
  headlinesData.zh = await newsResponse.json().catch((err) => {
    console.error(err);
    io.emit("error", { type: "ZH JSON parse", err: err });
  });

  //English News Fetch
  let enCountries = ["us", "uk"];
  country = enCountries[Math.floor(Math.random() * enCountries.length)];
  console.log("selected english country:", country);

  newsResponse = await fetch(
    "https://newsapi.org/v2/top-headlines?country=" +
      country +
      "&apiKey=" +
      newsApiKey
  ).catch((err) => {
    console.error(err);
    io.emit("error", { type: "newsapi.org", err: err });
  });
  headlinesData.en = await newsResponse.json().catch((err) => {
    console.error(err);
    io.emit("error", { type: "EN JSON parse", err: err });
  });

  //Translate Chinese News
  let translated = new Promise(function (resolve, reject) {
    translateData(headlinesData, (res) => {
      if (res != undefined) {
        resolve(res);
      } else {
        reject(console.error(err));
        io.emit("error", { type: "AWS", err: err });
      }
    });
  });

  let result;
  await translated
    .then((res) => {
      result = res;
    })
    .catch((err) => {
      console.error(err);
      io.emit("error", { type: "AWS", err: err });
    });
  return result;
}

//////////////////
//Handle sockets//
//////////////////
io.on("connect", function (socket) {
  console.log("We have a new client: " + socket.id);

  socket.on("getData", function (res) {
    console.log("fetching data...");
    main()
      .then((result) => {
        console.log("result sent to client!");
        socket.emit("result", result);
      })
      .catch((err) => console.error(err));
  });

  socket.on("disconnect", function () {
    console.log("Client has disconnected");
  });
});

//////////////
//Run Server//
//////////////
http.listen(port, () => {
  console.log("App listening at http://localhost:" + port);
});
