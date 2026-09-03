require('dotenv').config({
  path: require('path').join(__dirname, '..', '.env')
});

const { GoogleGenAI } = require('@google/genai');
const fs = require('fs');
const path = require('path');

async function testAssistant() {
  try {
    const apiKey = process.env.GOOGLE_API_KEY;

    if (!apiKey) {
      throw new Error('GOOGLE_API_KEY is not set in the .env file.');
    }

    const ai = new GoogleGenAI({
      apiKey: apiKey
    });

    const args = process.argv.slice(2);

    if (args.length < 2) {
      throw new Error(
        'Usage: node script.js <quiz-file> <percentage>'
      );
    }

    const quizFile = args[0];
    const percentage = args[1];

    // Convert supplied file path into an absolute path
    const quizPath = path.resolve(quizFile);

    if (!fs.existsSync(quizPath)) {
      throw new Error(`Quiz file not found: ${quizPath}`);
    }

    // Actually read the quiz file
    const quizContent = fs.readFileSync(quizPath, 'utf8');

    const prompt = `
You are a personalized learning assistant.

The student completed the following science quiz and scored ${percentage}%.

QUIZ:
----------------
${quizContent}
----------------

The quiz file contains questions, answer options, and the correct answer
letter after each question.

Important:
The student's individual answers are NOT available.
Therefore, do NOT claim that the student got any specific question wrong.

Based only on:
1. the topics covered by this quiz, and
2. the student's overall score of ${percentage}%,

provide:

- A short assessment of the student's performance.
- The main subject areas covered in the quiz.
- Topics worth reviewing to improve the score.
- Specific learning resources for those topics.
- A short recommended study plan.

Keep the response concise and useful.
`;

    const response = await ai.models.generateContent({
      model: 'gemini-3.7-flash',
      contents: prompt
    });

    console.log(response.text);

  } catch (error) {
    console.error('Error:', error.message || error);
    process.exitCode = 1;
  }
}

testAssistant();