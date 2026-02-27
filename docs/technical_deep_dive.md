# Technical Deep Dive

## 1) Architectural Explanation and Trade-offs

### End-to-End Flow

1. `main.c` loads runtime config (`PSM_PRODUCTS_CSV`, `PSM_SALES_CSV`).
2. Product and sales repositories hydrate in-memory state from CSV.
3. Controllers receive user actions from menu selections.
4. Services compute aggregate business metrics.
5. View renders outputs and captures validated input.
6. On exit, repositories persist state back to CSV files.

### Why MVC in a C CLI project

- enforce boundaries between UI, orchestration, and data logic
- allow isolated unit testing on business functions
- reduce blast radius of changes

### Key Trade-offs

- **Pros**: maintainability, testability, readability, interview clarity
- **Cons**: more files and interfaces than a monolith
- **Decision**: preferred maintainability and extensibility over minimum file count

### Alternatives Considered

- **Single-file procedural approach**: fast startup, poor scalability
- **Layered architecture without explicit controllers**: simpler but less explicit intent
- **OOP rewrite in C++/Java**: stronger abstraction, but changes language constraints

## 2) Interview Questions (Junior Level)

1. What is the role of repositories in this project?
2. Why separate report calculation into a service layer?
3. How do you validate CSV inputs before using them?
4. What does MVC mean in a command-line application?
5. How do unit tests improve confidence in C projects?
6. Why use environment variables for data paths?

## 3) Interview Questions (Senior Level)

1. How would you evolve this architecture for multi-user concurrency?
2. How would you add ACID-like guarantees for sales registration?
3. What observability signals would you collect in production?
4. How would you design multi-environment promotion (dev/stage/prod)?
5. How would you enforce data governance and retention policies?
6. How would you introduce model-based demand forecasting while keeping this architecture stable?

## 4) Critical Code Sections and Why They Matter

### `src/repositories/product_repository.c`

- Core responsibilities:
  - CSV parsing and product hydration
  - uniqueness and capacity constraints
  - persistent save-back to CSV
- Interview focus:
  - data integrity strategy
  - malformed row handling
  - idempotency assumptions

### `src/repositories/sale_repository.c`

- Core responsibilities:
  - sales validation (`quantity`, `date format`)
  - enforcing foreign-key-like relation to products
  - automatic sold-quantity accumulation
- Interview focus:
  - domain consistency checks
  - failure handling for unknown product references

### `src/services/report_service.c`

- Core responsibilities:
  - KPI computations (`total_revenue`, `total_units`, `best_seller`)
  - keeping business logic out of controllers/views
- Interview focus:
  - numeric accuracy and edge cases
  - where to place domain calculations in layered systems

### `src/controllers/product_controller.c`

- Core responsibilities:
  - flow orchestration from view to repositories
  - translating input operations into domain actions
- Interview focus:
  - controller boundary definition
  - error propagation strategy

### `.github/workflows/ci.yml`

- Core responsibilities:
  - compile + test gate on every push/PR
  - baseline quality enforcement before merge
- Interview focus:
  - minimal viable CI for native projects
  - extension path for static analysis and security scans
