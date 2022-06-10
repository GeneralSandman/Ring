Prism.languages.ring = Prism.languages.extend('clike', {
    'string': {
        pattern: /(^|[^\\])"(?:\\.|[^"\\\r\n])*"|`[^`]*`/,
        lookbehind: true,
        greedy: true
    },
    'keyword': /\b(?:break|case|chan|const|continue|int|default|defer|else|elseif|fallthrough|for|do|while|func|ring(?:to)?|if|return|switch|var|public|private|typedef|class|function)\b/,
    'boolean': /\b(?:_|false|true)\b/,
    'number': [
        // binary and octal integers
        /\b0(?:b[01_]+|o[0-7_]+)i?\b/i,
        // hexadecimal integers and floats
        /\b0x(?:[a-f\d_]+(?:\.[a-f\d_]*)?|\.[a-f\d_]+)(?:p[+-]?\d+(?:_\d+)*)?i?(?!\w)/i,
        // decimal integers and floats
        /(?:\b\d[\d_]*(?:\.[\d_]*)?|\B\.\d[\d_]*)(?:e[+-]?[\d_]+)?i?(?!\w)/i
    ],
    'operator': /[*\/%^!=]=?|\+[=+]?|-[=-]?|\|[=|]?|&(?:=|&|\^=?)?|>(?:>=?|=)?|<(?:<=?|=|-)?|:=|\.\.\./,
    'builtin': /\b(?:append|bool|int|double|byte|cap|close|complex|complex(?:64|128)|copy|delete|error|float(?:32|64)|u?int(?:8|16|32|64)?|imag|len|make|new|panic|print(?:ln)?|real|recover|rune|string|uintptr)\b/
});

Prism.languages.insertBefore('ring', 'string', {
    'char': {
        pattern: /'(?:\\.|[^'\\\r\n]){0,10}'/,
        greedy: true
    }
});

delete Prism.languages.ring['class-name'];