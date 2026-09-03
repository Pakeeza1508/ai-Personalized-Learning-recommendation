require('dotenv').config({ path: require('path').join(__dirname, '..', '.env') });
const { BardAPI } = require('bard-api-node');

async function testAssistant() {
  try {
  const bard = new BardAPI();
  const apiKey = process.env.GOOGLE_API_KEY;
  if (!apiKey) {
    throw new Error('GOOGLE_API_KEY is not set. Configure it in your environment before running the assistant.');
  }

  await bard.initializeChat(apiKey)
  const args = process.argv.slice(2);
  if (args.length < 2) {
    throw new Error('Usage: node script.js <quiz-file> <percentage>');
  }

  const response = await bard.getBardResponse(`${args[0]} percentage ${args[1]}. Recommend me sources to improve`);
  console.log(response.text);
  } catch (error) {
    console.error('Error:', error);
    process.exitCode = 1;
  }
}

testAssistant();