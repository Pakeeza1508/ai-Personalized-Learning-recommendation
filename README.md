# AI-Based Personalized Learning Recommendation System

> **Semester Project / Research Prototype**  
> This project was developed as an educational semester project to demonstrate object-oriented programming in C++, quiz-based learner assessment, local performance tracking, and an LLM-assisted recommendation pipeline. It is a research-oriented prototype rather than a production learning management system.

## Overview

The **AI-Based Personalized Learning Recommendation System** is a Windows console application that combines a rule-based assessment engine with a generative-AI recommendation layer.

A learner can:

- register or log in;
- choose a subject and difficulty level;
- select the number of quiz questions;
- answer multiple-choice questions;
- receive an automatically calculated score and percentage;
- receive AI-generated study recommendations based on the selected quiz, its content, and the learner's performance.

The application separates deterministic assessment from AI reasoning:

- **C++** handles user interaction, quiz selection, answer checking, scoring, and local persistence.
- **Node.js** acts as an AI integration layer.
- **Google Gemini** analyzes the quiz context and the learner's overall score to produce review topics, learning resources, and a short study plan.

This separation was intentional: the LLM does not decide whether an answer is correct. Grading remains deterministic and reproducible, while the LLM is used only for higher-level educational guidance.

---

## Research Motivation

Traditional quiz applications usually stop after displaying a score. This project explores a simple extension:

**Can an assessment result be converted into actionable learning guidance using a large language model?**

The prototype implements an early version of an intelligent educational system in which learner performance becomes an input to a recommendation component.

The current system performs **coarse-grained personalization** using:

- selected subject;
- selected difficulty level;
- quiz content;
- overall percentage.

It does not yet maintain a detailed learner model or infer exact misconceptions from individual incorrect answers. This makes the project a useful baseline for extending toward more advanced adaptive-learning research.

---

# System Architecture

```text
                    ┌──────────────────────────┐
                    │        Learner           │
                    │ register / login / quiz  │
                    └────────────┬─────────────┘
                                 │
                                 ▼
                    ┌──────────────────────────┐
                    │   C++ Console Dashboard  │
                    │                          │
                    │ - subject selection      │
                    │ - difficulty selection   │
                    │ - question presentation  │
                    │ - answer validation      │
                    │ - score calculation      │
                    └────────────┬─────────────┘
                                 │
                    quiz file + percentage
                                 │
                                 ▼
                    ┌──────────────────────────┐
                    │  Node.js AI Bridge       │
                    │  ai-model/script.js      │
                    │                          │
                    │ - reads quiz file        │
                    │ - loads API key          │
                    │ - builds AI prompt       │
                    │ - calls Gemini API       │
                    └────────────┬─────────────┘
                                 │
                  quiz content + performance
                                 │
                                 ▼
                    ┌──────────────────────────┐
                    │     Google Gemini        │
                    │                          │
                    │ - identifies subject     │
                    │   areas in the quiz      │
                    │ - suggests topics        │
                    │   worth reviewing        │
                    │ - recommends resources   │
                    │ - generates study plan   │
                    └────────────┬─────────────┘
                                 │
                                 ▼
                    ┌──────────────────────────┐
                    │ Personalized Guidance    │
                    │ printed in the console   │
                    └──────────────────────────┘
```

---

# AI Architecture

The AI component is intentionally implemented as a separate layer rather than embedding LLM logic directly into the C++ quiz engine.

## 1. Assessment Layer — C++

The C++ application is responsible for deterministic operations:

1. selecting the quiz file from the learner's subject and level;
2. loading questions and answer keys;
3. displaying the requested number of questions;
4. comparing learner responses with the stored answer key;
5. counting correct answers;
6. calculating the percentage;
7. saving local results;
8. invoking the AI recommendation process.

For a quiz with `N` questions:

```text
percentage = (correct_answers / N) × 100
```

The LLM is therefore **not involved in grading**.

---

## 2. Learner Performance Representation

After the quiz, the system creates a compact representation of the learner's current learning context.

Current signals include:

```text
Subject / difficulty
        +
Full quiz content
        +
Overall percentage
```

For example:

```text
ChemistryBasic.txt
80%
```

The Node.js layer also reads the actual contents of `ChemistryBasic.txt`, so Gemini receives the concepts represented in that assessment rather than only the filename.

This is more informative than sending a score alone because the LLM can infer which scientific areas were tested.

However, the current prototype does **not** send the learner's individual answers. Therefore, an 80% result tells the system that some improvement is needed, but it cannot truthfully determine exactly which questions the learner answered incorrectly.

---

## 3. AI Integration Layer — Node.js

The C++ application invokes:

```text
node ../ai-model/script.js <quiz-file> <percentage>
```

The Node.js program then:

1. validates the command-line arguments;
2. locates the requested quiz file;
3. reads the quiz using `fs.readFileSync()`;
4. reads `GOOGLE_API_KEY` from the root `.env` file;
5. initializes the official `@google/genai` SDK;
6. constructs an educational-analysis prompt;
7. sends the prompt to Gemini;
8. prints the generated recommendation back to the console.

Conceptually:

```text
C++ Assessment Engine
        │
        │ filename + percentage
        ▼
Node.js Integration Layer
        │
        │ quiz content + percentage + instructions
        ▼
Gemini
        │
        ▼
Educational Recommendation
```

---

## 4. LLM Reasoning Layer — Gemini

The LLM receives instructions to act as a personalized learning assistant.

Its input contains:

- the learner's overall score;
- the questions in the completed quiz;
- answer options;
- answer keys;
- explicit instructions not to claim knowledge of the learner's individual incorrect answers.

The generated response is structured around:

- performance assessment;
- main subject areas represented in the quiz;
- topics worth reviewing;
- learning-resource recommendations;
- a short study plan.

This keeps the AI role focused on **interpretation and guidance**, while objective assessment remains outside the model.

---

## 5. Recommendation Output

A typical response can contain:

```text
Performance Assessment
        ↓
Relevant Subject Areas
        ↓
Recommended Review Topics
        ↓
Learning Resources
        ↓
Short Study Plan
```

Because the response is generated by an LLM, the wording and resource suggestions may vary between runs.

---

# Personalization Logic

The current personalization pipeline is:

```text
Learner chooses subject + difficulty
                ↓
       Learner completes quiz
                ↓
     C++ calculates percentage
                ↓
 Node.js reads the completed quiz domain
                ↓
 Gemini analyzes quiz context + score
                ↓
 Personalized review recommendations
```

This should be described as **performance-aware recommendation**, not full adaptive learning.

The system currently personalizes recommendations using the learner's immediate assessment context. It does not yet implement:

- per-topic mastery scores;
- misconception detection from wrong answers;
- longitudinal learner profiles;
- automatic difficulty progression;
- knowledge tracing;
- automatic next-activity selection.

---

# Example Data Flow

Suppose a learner chooses:

```text
Subject: Chemistry
Difficulty: Basic
Questions: 5
Correct Answers: 4
```

The C++ application calculates:

```text
points = 4
percentage = 80
quiz = ChemistryBasic.txt
```

It then invokes:

```text
node ../ai-model/script.js ChemistryBasic.txt 80
```

The Node.js layer reads the complete quiz file and constructs an input conceptually similar to:

```text
The student completed the following science quiz and scored 80%.

[quiz questions, options, and answer keys]

Identify the subject areas represented in this assessment.
Recommend topics worth reviewing, useful learning resources,
and a short study plan.

Do not claim that a specific question was answered incorrectly,
because individual student responses are not available.
```

Gemini may then identify areas such as:

- chemical notation;
- states of matter;
- forces and energy;
- plant processes;
- basic astronomy;

and generate targeted revision suggestions.

---

# Core C++ Design

## `Question`

Represents a multiple-choice question containing:

- question text;
- four answer options;
- correct-answer key.

## `Subject`

An abstract base class responsible for the common quiz representation.

Concrete subject/difficulty classes inherit from it and load the corresponding text-based question bank.

Examples include:

```text
MathBasic
MathModerate
MathDifficult

ChemistryBasic
ChemistryModerate
ChemistryDifficult
```

## Quiz Selection

The application converts the learner's selected subject and level into a filename such as:

```text
Chemistry + Basic
        ↓
ChemistryBasic.txt
```

The matching subject class is then selected and used for the quiz.

## Quiz Complexity

For `N` displayed questions, the assessment loop is approximately:

- **Time complexity:** `O(N)`
- **Additional quiz-state space:** `O(1)` beyond the fixed question storage.

---

# Technology Stack

| Component | Technology | Responsibility |
|---|---|---|
| User interface | C++ console | Learner interaction and navigation |
| Assessment engine | C++ | Quiz loading, grading, score calculation |
| Local persistence | Text files | Users, quiz results, question banks |
| AI integration | Node.js | Connects C++ application with Gemini |
| LLM SDK | `@google/genai` | Official Gemini API client |
| AI model | Google Gemini | Educational analysis and recommendations |
| Secrets | `.env` | Local API-key configuration |
| Compiler | GCC / MinGW-w64 | Windows executable generation |

---

# Repository Layout

```text
.
├── ai-model/
│   ├── package.json
│   ├── package-lock.json
│   └── script.js
│
├── oop-final-dashboard/
│   ├── dashboard project.cpp
│   ├── quiz.h
│   ├── progress.h
│   ├── registeruser.h
│   ├── loginuser.h
│   ├── minhalchat.h
│   ├── decoration.h
│   └── *.txt                 # quiz question banks
│
├── .env.example
├── .gitignore
└── README.md
```

Generated executables, Node dependencies, secrets, and runtime user data should not be committed.

---

# Running the Project

## 1. Install Node.js Dependencies

```powershell
cd ai-model
npm install
```

## 2. Configure Gemini API Access

Create a root `.env` file:

```text
GOOGLE_API_KEY=your_api_key_here
```

Never commit the real `.env` file.

## 3. Compile the C++ Dashboard

Using a MinGW-w64 / MSYS2 GCC environment:

```powershell
cd oop-final-dashboard
g++ ".\dashboard project.cpp" -std=c++17 -static -static-libgcc -static-libstdc++ -o ".\dashboard-static.exe"
```

## 4. Run

```powershell
.\dashboard-static.exe
```

Internet access is required when the AI recommendation stage is invoked.

---

# Current Limitations

This project intentionally remains a semester-level prototype.

Current limitations include:

- personalization is based on assessment context and overall score rather than exact learner mistakes;
- individual answers are not passed to the recommendation model;
- questions are not tagged with fine-grained concepts;
- there is no persistent learner knowledge model;
- there is no automatic learning-path generation;
- difficulty progression is user-selected rather than adaptive;
- plain-text local user data is not appropriate for production use;
- the dashboard is Windows-console specific;
- LLM recommendations can vary and should not be treated as deterministic assessment results.

---

# Research Relevance to MITACS GRI 2027

This project is particularly relevant to my selected MITACS Globalink Research Internship project:

**Project 51202 — LLM-Powered Intelligent Educational Systems, Athabasca University.**

That research direction focuses on using large language models in personalized online learning, including areas such as:

- learner-aware educational support;
- personalized learning paths;
- planning learning activities;
- adaptive practice;
- formative assessment;
- structured representations of curriculum and learner knowledge.

My semester project implements a much smaller prototype of the same general research problem:

```text
Assessment
    ↓
Learner-performance signal
    ↓
LLM interpretation
    ↓
Personalized learning guidance
```

The current project does not yet implement knowledge graphs or a full adaptive-learning policy. Instead, it gave me practical experience with an important first step: connecting deterministic learner assessment with an LLM-based recommendation component.

The architecture also exposes clear research extensions.

## Possible Research Extension

A stronger version could evolve from:

```text
quiz + overall score
        ↓
LLM recommendation
```

to:

```text
question-level learner responses
        ↓
concept / topic tagging
        ↓
learner mastery representation
        ↓
knowledge or cognitive graph
        ↓
LLM-based learning-path planner
        ↓
adaptive learning activity
        ↓
formative reassessment
        ↓
updated learner model
```

This would allow the system to answer more meaningful educational questions:

- Which concepts has the learner mastered?
- Which misconceptions repeatedly appear?
- Which prerequisite concept is missing?
- What should the learner study next?
- Should the next activity explain, demonstrate, practise, or assess?
- Has the learner improved after the intervention?

This progression—from a score-based recommendation prototype toward a structured learner model and adaptive learning path—is the main research direction I would be interested in exploring further.

---

# What I Learned From This Project

The project gave me hands-on experience with:

- designing an object-oriented C++ application;
- separating assessment logic from generative-AI reasoning;
- integrating a C++ program with a Node.js AI service;
- working with an external LLM API;
- managing API keys securely through environment variables;
- converting structured assessment context into an LLM prompt;
- evaluating the difference between a recommendation system and a genuinely adaptive learning system;
- identifying architectural limitations that would need to be solved for research-grade personalization.

A key lesson was that simply adding an LLM does not automatically make a learning system adaptive. Meaningful personalization requires richer learner-state information, concept-level assessment, and mechanisms for updating future learning activities based on evidence of performance.

---

# Authors

- Noor Fatima
- Minhal Zubair
- Pakeeza Khalid
