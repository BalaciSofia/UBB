import assert from "node:assert/strict";
import { createRequire } from "node:module";
import test from "node:test";

const require = createRequire(import.meta.url);
const {
  validateArticlePayload,
  validateArticleContentPayload,
  validateCredentialsPayload,
  validateStatusPayload,
} = require("../src/validation/articleValidation.js");

test("accepts a valid editor article payload", () => {
  const errors = validateArticlePayload({
    title: "A serious story about thought and heat",
    journalistIds: [2, 3],
    paragraphs: [
      {
        text: "This paragraph is long enough to pass backend validation.",
        imagePaths: ["/images/example.jpg"],
        comments: ["Internal editor note"],
      },
    ],
  });

  assert.deepEqual(errors, []);
});

test("rejects articles without one or two journalists", () => {
  const errors = validateArticlePayload({
    title: "Short team",
    journalistIds: [2, 3, 4],
    paragraphs: [
      {
        text: "This paragraph is long enough to pass backend validation.",
        imagePaths: [],
        comments: [],
      },
    ],
  });

  assert.match(errors.join(" "), /one or two journalists/);
});

test("rejects invalid article statuses", () => {
  const errors = validateStatusPayload({ status: "archived" });

  assert.match(errors.join(" "), /started, pending, or finished/);
});

test("accepts journalist content payload without comments or title changes", () => {
  const errors = validateArticleContentPayload({
    paragraphs: [
      {
        text: "A journalist can rewrite paragraph copy and keep it long enough.",
        imagePaths: ["/images/assignment.jpg"],
      },
    ],
  });

  assert.deepEqual(errors, []);
});

test("rejects invalid credentials payloads", () => {
  const errors = validateCredentialsPayload({
    username: "ab",
    password: "",
  });

  assert.equal(errors.length, 2);
});
