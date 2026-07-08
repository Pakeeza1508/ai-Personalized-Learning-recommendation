 const { BardAPI } = require('bard-api-node');

async function testAssistant() {
  try { // Initialize BardAPI object const bard = new BardAPI();
  const bard = new BardAPI();
  // Set API key
  const apiKey = 'AIzaSyDSbbAUVoeLO0yj5zzzFEmW5RytO9We3SY'; // Replace 'YOUR_API_KEY' with the obtained API key
  // Initialize chat with API key
  await bard.initializeChat(apiKey)
  // Send a query to Bard
  const args = process.argv.slice(2);
  const response = await bard.getBardResponse(`${args[0]} percentage ${args[1]}. Recommend me sources to improve`);
  console.log(response.text);
  } catch (error) {
    console.error('Error:', error);
  }
}

testAssistant();