Prism.languages.shell = Prism.languages.extend('clike', {
    'string': {
        pattern: /(^|[^\\])"(?:\\.|[^"\\\r\n])*"|`[^`]*`/,
        lookbehind: true,
        greedy: true
    },
    'keyword': /\b(?:git|cd|mkdir|make|ring)\b/,
    'boolean': /\b(?:_|false|true)\b/,
    'number': [
        // binary and octal integers
        /\b0(?:b[01_]+|o[0-7_]+)i?\b/i,
        // hexadecimal integers and floats
        /\b0x(?:[a-f\d_]+(?:\.[a-f\d_]*)?|\.[a-f\d_]+)(?:p[+-]?\d+(?:_\d+)*)?i?(?!\w)/i,
        // decimal integers and floats
        /(?:\b\d[\d_]*(?:\.[\d_]*)?|\B\.\d[\d_]*)(?:e[+-]?[\d_]+)?i?(?!\w)/i
    ],
    'operator': /&&/,
    'builtin': /\b(?:clone)\b/
});

Prism.languages.insertBefore('ring', 'string', {
    'char': {
        pattern: /'(?:\\.|[^'\\\r\n]){0,10}'/,
        greedy: true
    }
});

delete Prism.languages.shell['class-name'];