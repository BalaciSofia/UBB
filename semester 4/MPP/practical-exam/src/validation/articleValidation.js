const VALID_STATUSES = ["started", "pending", "finished"];

function validateArticlePayload(payload) {
  const errors = [];

  if (!payload || typeof payload !== "object") {
    return ["Article payload is required."];
  }

  if (typeof payload.title !== "string" || payload.title.trim().length < 3) {
    errors.push("Title must have at least 3 characters.");
  }

  if (
    !Array.isArray(payload.journalistIds) ||
    payload.journalistIds.length < 1 ||
    payload.journalistIds.length > 2
  ) {
    errors.push("An article must have one or two journalists.");
  } else if (
    payload.journalistIds.some(
      (journalistId) =>
        !Number.isInteger(Number(journalistId)) || Number(journalistId) <= 0,
    )
  ) {
    errors.push("Journalist ids must be positive numbers.");
  }

  if (!Array.isArray(payload.paragraphs) || payload.paragraphs.length < 1) {
    errors.push("At least one paragraph is required.");
  } else {
    payload.paragraphs.forEach((paragraph, index) => {
      if (
        !paragraph ||
        typeof paragraph.text !== "string" ||
        paragraph.text.trim().length < 20
      ) {
        errors.push(`Paragraph ${index + 1} must have at least 20 characters.`);
      }

      if (!Array.isArray(paragraph.imagePaths)) {
        errors.push(`Paragraph ${index + 1} images must be a list.`);
      } else if (
        paragraph.imagePaths.some(
          (path) => typeof path !== "string" || path.trim().length < 1,
        )
      ) {
        errors.push(`Paragraph ${index + 1} image paths cannot be empty.`);
      }

      if (!Array.isArray(paragraph.comments)) {
        errors.push(`Paragraph ${index + 1} comments must be a list.`);
      } else if (
        paragraph.comments.some(
          (comment) =>
            typeof comment !== "string" || comment.trim().length < 3,
        )
      ) {
        errors.push(`Paragraph ${index + 1} comments must have text.`);
      }
    });
  }

  return errors;
}

function validateArticleContentPayload(payload) {
  const errors = [];

  if (!payload || typeof payload !== "object") {
    return ["Article payload is required."];
  }

  if (!Array.isArray(payload.paragraphs) || payload.paragraphs.length < 1) {
    errors.push("At least one paragraph is required.");
  } else {
    payload.paragraphs.forEach((paragraph, index) => {
      if (
        !paragraph ||
        typeof paragraph.text !== "string" ||
        paragraph.text.trim().length < 20
      ) {
        errors.push(`Paragraph ${index + 1} must have at least 20 characters.`);
      }

      if (!Array.isArray(paragraph.imagePaths)) {
        errors.push(`Paragraph ${index + 1} images must be a list.`);
      } else if (
        paragraph.imagePaths.some(
          (path) => typeof path !== "string" || path.trim().length < 1,
        )
      ) {
        errors.push(`Paragraph ${index + 1} image paths cannot be empty.`);
      }
    });
  }

  return errors;
}

function validateStatusPayload(payload) {
  if (!payload || !VALID_STATUSES.includes(payload.status)) {
    return ["Status must be started, pending, or finished."];
  }

  return [];
}

function validateCredentialsPayload(payload) {
  const errors = [];

  if (!payload || typeof payload !== "object") {
    return ["Credentials are required."];
  }

  if (typeof payload.username !== "string" || payload.username.trim().length < 3) {
    errors.push("Username must have at least 3 characters.");
  }

  if (typeof payload.password !== "string" || payload.password.trim().length < 3) {
    errors.push("Password must have at least 3 characters.");
  }

  return errors;
}

module.exports = {
  VALID_STATUSES,
  validateArticleContentPayload,
  validateArticlePayload,
  validateCredentialsPayload,
  validateStatusPayload,
};
