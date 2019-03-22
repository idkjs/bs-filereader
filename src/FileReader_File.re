open FileReader__;

type t = file;

include FileReader_BlobLike.Make({
  type nonrec t = t;
});

[@bs.get] external name: t => string = "name";
[@bs.get] external lastModified: t => float = "lastModified";

external asBlob: t => FileReader_Blob.t = "%identity";

type options = {
  .
  "type": Js.Nullable.t(string),
  "lastModified": Js.Nullable.t(float),
};

[@bs.new]
external make_: (array(Js.Json.t), string, Js.Nullable.t(options)) => t =
  "File";

[@bs.new] external make__: (array(Js.Json.t), string) => t = "File";

let make =
    (
      parts: array(blobPart),
      name: string,
      ~type_: option(string)=?,
      ~lastModified: option(float)=?,
      (),
    ) => {
  let parts = parts->Belt.Array.map(blobPartToJson);
  switch (type_, lastModified) {
  | (None, None) => make__(parts, name)
  | (type_, lastModified) =>
    let options =
      Js.Nullable.return({
        "type": type_->Js.Nullable.fromOption,
        "lastModified": lastModified->Js.Nullable.fromOption,
      });
    make_(parts, name, options);
  };
};
