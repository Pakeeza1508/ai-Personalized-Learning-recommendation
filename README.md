# AI-Based Personalized Learning Recommendation System

> **Semester project:** This educational semester project demonstrates object-oriented C++, file-based quiz management, and an AI-assisted learning recommendation workflow. It is not a production learning management system.

## Overview

This Windows console application lets a learner register or log in, select a subject, difficulty level, and number of questions, and take a multiple-choice quiz. It calculates the result, saves it locally, and asks a Google Bard/Gemini-compatible API wrapper for study-source recommendations.

The C++ dashboard is the main application. The Node.js program in `ai-model/` is an external recommendation assistant invoked after a quiz. A duplicate script in `oop final dashboard/` is retained for compatibility with the original layout.

## Technology Stack

- C++ with object-oriented programming
- MinGW/Dev-C++ project files and Windows console APIs
- Node.js for the AI recommendation bridge
- `bard-api-node` and `bard-ai` npm packages
- Plain-text files for question banks and local application data

## Student Inputs and Performance Data

The learner provides a username/password during registration or login, then selects:

1. Subject: Math, Physics, Chemistry, Computer, English, Science, or General.
2. Difficulty: Basic, Moderate, or Difficult. `High` is also accepted internally.
3. Number of questions from 1 to 20.
4. One answer (`a`, `b`, `c`, or `d`) for each displayed question.

The application derives the correct-answer count, the percentage `(correct answers / selected questions) * 100`, and the selected quiz filename such as `ChemistryBasic.txt`.

Results are appended to `marks.txt`; the selected quiz is appended to `selectedsubject.txt`. These are local student/application data files and should not be committed to a public repository.

## Exact Personalization and Recommendation Logic

1. The user selects a subject and level.
2. `capitalizeFirst()` normalizes the first character and `constructFilename()` creates `<Subject><Level>.txt`.
3. `takequiz()` selects the matching derived `Subject` class.
4. The first `N` questions from that file are displayed.
5. Each answer is compared with the answer key in the question file.
6. The score and percentage are calculated and saved.
7. C++ invokes `node ../ai-model/script.js <quiz-file> <percentage>`.
8. Node sends this prompt to the external assistant: `ChemistryBasic.txt percentage 80. Recommend me sources to improve`.
9. The returned recommendation text is printed in the console.

Personalization currently uses the quiz category (subject plus level) and overall percentage. The code does not calculate per-topic accuracy, retain a per-student performance history, or automatically choose the next difficulty level. The recommendation is AI-generated, but quiz selection and grading are handled by C++.

## Classes, Data Structures, and Algorithms

- `Question` is a struct containing the question, four options, and answer key.
- `Subject` is an abstract base class with a fixed `Question questions[20]` array.
- Concrete classes such as `MathBasic`, `ChemistryDifficult`, and `EnglishModerate` inherit from `Subject` and load their matching text file.
- `takequiz()` uses an array of 20 `Subject*` objects and conditional mapping to select the requested class.
- `load_file()` reads each question as six lines: question, four options, and answer key.
- `ask_questions()` loops through the requested questions, compares answers, and calculates the percentage.
- `ifstream` and `ofstream` provide local file persistence.

The quiz algorithm is linear in the number of displayed questions: $O(N)$ time and $O(1)$ additional quiz-state space, excluding the fixed 20-question array.

## Weak Areas and Adaptive Paths

The current implementation identifies weakness only at the **quiz level**: a low percentage indicates that the learner needs improvement in the selected subject/difficulty category. Questions are not tagged by topic, so the system cannot identify a specific sub-area such as algebra or grammar.

There is no automatic multi-step adaptive path yet. The implemented path is:

`user-selected subject/level -> quiz -> percentage -> AI study-source recommendation`

The learner must manually choose a later quiz. A future version could tag each question by topic, store attempts per learner, and use score thresholds to select revision or a different level automatically.

## AI/API Integration

An external LLM/API really exists in `ai-model/script.js` and the compatibility copy under `oop final dashboard/`, using `bard-api-node`.

- **Purpose:** turn the selected quiz category and score into readable study-source suggestions.
- **Input:** quiz filename and percentage only; no complete student profile or answer history.
- **Output:** free-form recommendation text printed to the console.
- **Not performed by the LLM:** grading, question selection, percentage calculation, or C++ class selection.

The package name reflects the original Bard integration. Google Bard was later rebranded as Gemini, and this third-party wrapper may require maintenance if the upstream service changes.

## Secure API Key Setup

The key is read from the `GOOGLE_API_KEY` environment variable and is not stored in source code.

PowerShell:

```powershell
$env:GOOGLE_API_KEY = "your_new_key_here"
node .\ai-model\script.js ChemistryBasic.txt 80
```

Command Prompt:

```bat
set GOOGLE_API_KEY=your_new_key_here
node ai-model\script.js ChemistryBasic.txt 80
```

Install dependencies first:

```powershell
cd ai-model
npm install
```

The included `.env.example` documents the variable name, and both Node scripts load the root `.env` automatically. Never commit `.env`, real API keys, `node_modules`, or generated student data. Because the old key was previously committed, revoke/delete it in Google AI Studio and create a replacement before making the repository public. Removing it from the latest file does not remove it from Git history; use an approved secret-removal/history-rewrite tool on the private repository before the public push.

## Example: Input -> Decision -> Recommendation

**Input:** Chemistry, Basic, 5 questions; the learner answers 4 correctly.

**Decision:** `ChemistryBasic.txt` is selected, `points = 4`, `percentage = 80`, and C++ calls:

```text
node ../ai-model/script.js ChemistryBasic.txt 80
```

**Recommendation:** The LLM receives `ChemistryBasic.txt percentage 80. Recommend me sources to improve` and may return chemistry revision sources and practice advice. The exact response can vary because it is generated by an external service.

## Representative Output

```text
Total Points: 4
Your Percentage: 80%
Loading suggestions...
Review introductory chemistry concepts and practise questions from a trusted source.
```

The project is console-based, so its primary output is text rather than a web interface. A screenshot of a captured console run can be added to this section; the text output above is a reproducible example.

## Test Cases

| Case | Input | Expected result |
|---|---|---|
| Valid basic quiz | Chemistry, Basic, 5; 4 correct | Loads `ChemistryBasic.txt`, records 4 and 80%, invokes assistant |
| Perfect score | Valid quiz; all answers correct | Percentage is 100% and recommendation call runs |
| Zero score | Valid quiz; no answers correct | Percentage is 0% and improvement recommendation is requested |
| Invalid subject | Biology, Basic, 5 | Prints invalid subject/level message |
| Invalid level | Math, Advanced, 5 | Prints invalid subject/level message |
| Missing key | `GOOGLE_API_KEY` unset | Node stops with a clear configuration error and sends no request |
| Missing arguments | `node script.js` | Node prints a usage error |
| Missing question file | Unavailable quiz file | C++ reports a file-open failure under current implementation |

## Limitations

- The third-party Bard/Gemini wrapper requires internet access and a valid key.
- Recommendations may be generic because only filename and score are sent.
- Questions are taken in file order, not selected randomly or by mastery.
- There is no topic tagging, longitudinal student model, or automatic level progression.
- Plain-text credentials and scores are unsuitable for production privacy or concurrent multi-user use.
- Windows-specific APIs and shell commands make the dashboard non-portable as written.
- Input validation is limited; malformed files or invalid question counts can behave incorrectly.
- The npm `test` script is still a placeholder; current verification is manual.

## Repository Layout

```text
.
├── ai-model/                 Node.js recommendation bridge
├── oop final dashboard/      C++ dashboard, headers, quiz banks, project files
├── .env.example              API variable template
├── .gitignore                Secret, build, dependency, and local-data exclusions
└── README.md                 Project documentation
```

## Authors

- Noor Fatima
- Minhal Zubair
- Pakeeza Khalid
