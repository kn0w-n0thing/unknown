const {getNews} = require('./people-news')
const {translate} = require('./baidu-translate')

let headlinesData = {zh: {}};

async function getHeadlines() {
    let newsList = await getNews();
    headlinesData.zh.articles = newsList;
    const titles = collectTitles(headlinesData.zh.articles);
    const translatedTitles = await translate(titles);
    addTranslatedTitles(headlinesData.zh.articles, translatedTitles);
    // filter articles with an empty translated title
    headlinesData.zh.articles = headlinesData.zh.articles.filter( article =>
        article.translation.length !== 0 && !/^(\s)*$/.test(article.translation)
    )
    return headlinesData;
}

function collectTitles(articles) {
    let titles = [];
    articles.forEach(article => titles.push(article.title));
    return titles;
}

function addTranslatedTitles(articles, translatedTitles) {
    articles.forEach((article, index) => article.translation = translatedTitles[index])
}

module.exports = {getHeadlines}
