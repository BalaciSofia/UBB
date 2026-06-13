import type { Metadata } from "next";
import "./globals.css";

export const metadata: Metadata = {
  title: "Teoria Transpiratiei",
  description: "Un ziar experimental despre idei, efort si sudoare.",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="ro">
      <body>{children}</body>
    </html>
  );
}
