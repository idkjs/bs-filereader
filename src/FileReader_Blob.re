open FileReader__;

type t = blob;

include FileReader_BlobLike.Make({
  type nonrec t = t;
});

let asFile_: t => Js.Nullable.t(t) = [%raw
  {|
function(blob) {
  if (blob instanceof File) {
    return blob;
  } else {
    return null;
  }
}
|}
];

let asFile = blob => asFile_(blob)->Js.Nullable.toOption;

type options = {
  .
  "type": Js.Nullable.t(string),
  "endings": Js.Nullable.t(string) /* This API has not been standardized. */
};

[@bs.new]
external make_: (array(Js.Json.t), Js.Nullable.t(options)) => t = "Blob";

[@bs.new] external make__: array(Js.Json.t) => t = "Blob";

let make =
    (
      parts: array(FileReader__.blobPart),
      ~type_: option(string)=?,
      ~endings: option(string)=?,
      (),
    ) => {
  let parts = parts->Belt.Array.map(blobPartToJson);

  switch (type_, endings) {
  | (None, None) => make__(parts)
  | (type_, endings) =>
    let opts =
      Js.Nullable.return({
        "type": type_->Js.Nullable.fromOption,
        "endings": endings->Js.Nullable.fromOption,
      });
    make_(parts, opts);
  };
};
