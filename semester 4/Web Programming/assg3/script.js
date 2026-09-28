const links = document.querySelectorAll("a");

links.forEach(link => {
    if (link.href.startsWith("https://www.scs.ubbcluj.ro")) {
        const p = document.createElement("p");
        p.textContent = link.textContent;
        link.replaceWith(p);
    }
});
