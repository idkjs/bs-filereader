open FileReader;
open Belt;

let fr = FileReader.make();

let printResult = res =>
  switch (res) {
  | Some(`String(s)) => Js.log2("result is string", s)
  | Some(`ArrayBuffer(ab)) => Js.log2("result is array buffer", ab)
  | None => Js.log("result is none")
  };
fr->result;
printResult(fr->result);

let error = fr->error;
Js.log2("error", error);
Js.log2("error is some", error->Option.isSome);

fr->onload(e => {
  Js.log("onload");
  Js.log2("onload e", e);

  printResult(fr->result);
});

fr->onerror(e => {
  Js.log("onerror");
  Js.log2("onerror e", e);
});

let file = File.makeUnsafe(~bits=[|Js.Typed_array.Uint8Array.make([|192, 193|])|], ~name="file1", ());
Js.log2("file name", file->File.name);
Js.log2("file last mod", file->File.lastModified);
Js.log2("file size", file->File.size);
Js.log2("file type", file->File.type_);

let blob = Blob.makeUnsafe([|Js.Typed_array.Uint8Array.make([|65, 66|])|], ());
/* should not compile */
/*Js.log2("blob name", blob->File.name);*/

/*fr->readAsArrayBuffer(file->File.asBlob);*/
/*fr->readAsBinaryString(file->File.asBlob);*/
fr->readAsText(file->File.asBlob, ~encoding="Windows-1251", ());
/*fr->readAsDataURL(file->File.asBlob);*/

/*fr->readAsText(blob, ());*/

open Js.Promise;

blob->Blob.toArrayBuffer
|> then_(ab => {
     Js.log2("blobToArrayBuffer ok", ab);
     resolve();
   });

blob->Blob.toDataURL
|> then_(s => {
     Js.log2("blobToDataURL ok", s);
     resolve();
   });

blob->Blob.toText()
|> then_(s => {
     Js.log2("blobToText ok", s);
     resolve();
   });
