/**
 * Baidu Translation Reference: https://cloud.baidu.com/doc/MT/s/4kqryjku9
 */
const config = require("../assets/config.json");
const axios = require('axios');

const apiKey = config.baidu.apiKey;
const secretKey = config.baidu.secretKey;

// buffer access token
let accessToken;
// let expiredTimeSec = 0;

const seperator = '\n\n';

async function getAccessToken() {
    const url = `https://aip.baidubce.com/oauth/2.0/token?client_id=${apiKey}&client_secret=${secretKey}&grant_type=client_credentials`;
    const data = {
        'headers': {
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        }
    };

    try {
        const response = await axios.post(url, data);
        accessToken = response.data['access_token'];
    } catch (error) {
        throw error;
    }

    return accessToken;
}

// Referring to the document of Baidu, input limit size of one translate RPC is 6000 BYTES, namely 3000 CHARACTERS.
// In case of rpc failure, here we set the limit to 2000 CHARACTERS.
async function translate(input) {
    const characterLimit = 2000;
    let output = [];
    let startIndex = 0, endIndex = 0;
    // accumulated character number
    let accString = '';

    while (startIndex < input.length) {
        if (endIndex >= input.length) {
            output = output.concat(await translateRpc(accString))
            break;
        }

        if (accString.length + input[endIndex].length < characterLimit) {
            accString += input[endIndex] + seperator;
            endIndex++;
        } else {
            output = output.concat(await translateRpc(accString));
            startIndex = endIndex;
            accString = '';
        }
    }
    return output;
}

async function translateRpc(input) {
    let accessToken = await getAccessToken();
    const url = `https://aip.baidubce.com/rpc/2.0/mt/texttrans/v1?access_token=${accessToken}`;
    const data = {
        'headers': {
            'Content-Type': 'application/json',
            'Accept': 'application/json',
        },
        'q': input,
        'from': 'zh',
        'to': 'en'
    };

    try {
        const response = await axios.post(url, data);
        let output = [];
        response.data.result.trans_result.forEach(trans_result => {
             output.push(trans_result.dst);
        });
        return output;
    } catch (error) {
        throw error;
    }
}

module.exports = {translate: translate};