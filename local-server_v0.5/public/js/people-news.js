const axios = require('axios')
const {XMLParser} = require('fast-xml-parser')

const getNews = async () => {
    const rssUrl = 'https://www.people.com.cn/rss/politics.xml';

    let titleList = [];
    try {
        const response = await axios.get(rssUrl)
        let xml = (new XMLParser()).parse(response.data);
        xml.rss.channel.item.forEach(item => titleList.push(item));
        return titleList;
    } catch (error) {
        throw error;
    }
};

module.exports = {getNews};
