# Logger Overview

- `Logger` with `ConsoleSink`, `JsonFileSink`, `BufferedTextSink`.
- Contexts: `logger->withContext("Serialization")`
- Fields: `logger->info("message", {{"key","value"}})`
- Scope timing and simple rate limiting.
