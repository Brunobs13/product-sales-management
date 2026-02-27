# Portfolio-Ready Assets

## LinkedIn Version (Short)

Refactored a monolithic C sales app into a production-style MVC architecture with repositories, service layer, controllers, and view separation. Added unit tests, CI pipeline, secure runtime config, and enterprise-grade documentation.

## CV Version (Technical)

Designed and implemented an MVC-based Product Sales Management system in C11, replacing a procedural monolith with modular layers (`repositories`, `services`, `controllers`, `views`). Built deterministic CSV persistence, input validation, unit tests, and GitHub Actions CI for compile/test gating. Delivered security hygiene (`.env` templates, hardened `.gitignore`) and technical documentation aligned with MLOps/DevOps review standards.

## 60-Second Pitch

I rebuilt this project from a single C file into a maintainable MVC architecture. The repositories now handle validated CSV persistence, controllers orchestrate user flows, and a dedicated service layer computes business KPIs like revenue and best sellers. I added unit tests and GitHub Actions so each change is automatically compiled and verified. I also introduced environment-based configuration and security hygiene, plus a full technical audit and interview-focused documentation. The result is a codebase that is easier to scale, safer to operate, and much stronger for technical interviews.

## 5-Minute Technical Pitch

This repository started as a monolithic C script with tightly coupled concerns. I decomposed it into an MVC architecture:

- Model structures define `Product`, `Sale`, and in-memory registries.
- Repositories own data contracts, CSV parsing, validation, and persistence.
- Controllers orchestrate user intent and error handling.
- A service layer isolates reporting logic so business calculations remain testable.
- The view layer is responsible only for terminal input/output.

From an engineering quality perspective, I implemented a build system with strict compiler flags and a CI pipeline that runs compile and unit tests on each push and pull request. This ensures regressions are caught early.

From a security and operational lens, I removed implicit local assumptions by introducing environment-driven paths and templates (`.env.example`). I hardened `.gitignore` to avoid sensitive/local artifact leakage and included MLOps-oriented ignore patterns for future evolution.

From a product perspective, the architecture now supports clear extension points: transactional storage, API exposure, observability, and even ML forecasting integration with MLflow + DVC for experiment and data lineage.

Overall, the project now reflects real-world engineering standards for maintainability, reviewability, and production-readiness.
