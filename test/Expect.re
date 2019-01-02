[@bs.val] [@bs.module "expect"] external assert_: 'a => unit = "assert"; 


[@bs.val] [@bs.module "./expect"] external expectToBe: ('a, 'a) => unit = "expectToBe";

[@bs.val] [@bs.module "./expect"] external expectToEqual: ('a, 'a) => unit = "expectToEqual";

[@bs.val] [@bs.module "./expect"] external expectToEqualAny: ('a, 'b) => unit = "expectToEqual";

type ctor;
let blob_ctor: ctor = [%raw "Blob"];
let array_buffer_ctor: ctor = [%raw "ArrayBuffer"];

[@bs.val] [@bs.module "./expect"] external expectInstanceOf: ('a, ctor) => unit = "expectInstanceOf";

