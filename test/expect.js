
export function expectToBe(a, b) {
    let expect = require("expect");
    expect(a).toBe(b);
}

export function expectToEqual(a, b) {
    let expect = require("expect");
    expect(a).toEqual(b);
}

export function expectInstanceOf(a, b) {
    let expect = require("expect");
    expect(a instanceof b).toEqual(true);
}
