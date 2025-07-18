# Fluxograma da Busca Linear Iterativa

\`\`\`mermaid
graph TD
    A(Início) --> B{Para cada elemento no array, do primeiro ao último};
    B -- Sim --> C{Elemento atual é igual à chave?};
    C -- Sim --> D(Retorna a posição do elemento);
    C -- Não --> E{Mais elementos no array?};
    E -- Sim --> B;
    E -- Não --> F(Retorna -1 (não encontrado));
    D --> G(Fim);
    F --> G(Fim);
\`\`\`