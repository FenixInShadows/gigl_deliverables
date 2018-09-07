# gigl_deliverables

This repo contains a collection of resources about the Grammatical Item Generation Language (GIGL) project, by the Applied Motion Lab (AML) in the University of Minnesota.

The following is an overview of the content.

- The "ableC.jar" is the GIGL-C++ translator, the key part for compling GIGL code.

- The "include" directory contains the GIGL auxilliary library sources (however, be clear that GIGL is not a library but a DSL), which is needed for the translated code to compile; they may optionally be used by users directly

- The "demo" directory contains demo projects containing prepared GIGL code. The "Windows" and "Unix" subfolders has the demos setup for the corresponding operating system. There are five demos currently available.
  - HelloWorld: An example of entry level GIGL programming, which is a simple probabilistic text generation.
  - Monster: An example of generating dungeon monsters with very simple attributes.
  - Quiz: An example of generating arithmetic quizzes.
  - LSystemTree: An example of generating trees based on an L-system grammar.
  - Dungeon_BSP: An example of generating dungeon levels (maps).

- The "exercises" directory contains exercise projects requiring GIGL code to be filled in. The "Windows" and "Unix" subfolders has the demos setup for the corresponding operating system. The "solution" subfolder contains the solutions to the exercises. There are two exercises currently available.
  - GoodMorning: A slightly more complex (still very simple) text generation than the Hello World demo.
  - FancyMonster: A more complicated monster generation than the Monster demo.
  
- The instructions can be found in the text documents or, as a better version, on the project website.
  - The instructions for custom use without prior setup: the txt in the root directory of the repo or https://sites.google.com/a/umn.edu/grammatical-item-generation-language/instructions
  - The instructions for demos: the txt in the demo directory or https://sites.google.com/a/umn.edu/grammatical-item-generation-language/demos
  - The instructions for exercises: the txt in the exercise directory or https://sites.google.com/a/umn.edu/grammatical-item-generation-language/walk-trough-practices
