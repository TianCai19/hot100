/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./pages/**/*.{js,jsx,mdx}",
    "./components/**/*.{js,jsx}",
    "./content/posts/**/*.{md,mdx}",
  ],
  theme: {
    extend: {
      colors: {
        ink: "#0b1221",
        panel: "#0f172a",
      },
      boxShadow: {
        card: "0 20px 70px rgba(59,130,246,0.08)",
      },
      typography: {
        DEFAULT: {
          css: {
            maxWidth: "80ch",
            color: "#e5e7eb",
            h1: { color: "#bfdbfe" },
            h2: { color: "#e5e7eb" },
            h3: { color: "#e5e7eb" },
            strong: { color: "#f8fafc" },
            a: { color: "#60a5fa" },
            code: {
              color: "#bfdbfe",
              backgroundColor: "#111827",
              padding: "0.25rem 0.35rem",
              borderRadius: "0.375rem",
            },
            "code::before": { display: "none" },
            "code::after": { display: "none" },
            pre: {
              backgroundColor: "#0b1221",
              border: "1px solid #1f2937",
              borderRadius: "0.75rem",
            },
            table: { color: "#e5e7eb" },
            th: { color: "#e5e7eb" },
            blockquote: {
              borderLeftColor: "#334155",
              color: "#e2e8f0",
            },
          },
        },
        invert: {
          css: {
            "--tw-prose-body": "#e5e7eb",
            "--tw-prose-headings": "#f8fafc",
            "--tw-prose-links": "#93c5fd",
            "--tw-prose-bold": "#f8fafc",
            "--tw-prose-quote-borders": "#334155",
            "--tw-prose-captions": "#cbd5e1",
            "--tw-prose-code": "#bfdbfe",
            "--tw-prose-pre-code": "#e5e7eb",
            "--tw-prose-pre-bg": "#0b1221",
            code: {
              backgroundColor: "#111827",
              padding: "0.25rem 0.35rem",
              borderRadius: "0.375rem",
            },
            "code::before": { display: "none" },
            "code::after": { display: "none" },
          },
        },
      },
    },
  },
  plugins: [require("@tailwindcss/typography")],
};
