type t = FileReader_Types.blob;

include FileReader_BlobLike.Make({
  type nonrec t = t;
});

type options = {
  .
  "type": Js.Nullable.t(string),
  "endings": Js.Nullable.t(string) /* This API has not been standardized. */
};

[@bs.new]
external make_: (array(Js.Json.t), Js.Nullable.t(options)) => t = "Blob";

let make =
    (
      parts: array(FileReader_BlobPart.t),
      ~type_: option(string)=?,
      ~endings: option(string)=?,
      (),
    ) => {
  let parts = parts->Belt.Array.map(FileReader_BlobPart.toJson);
  let options =
    switch (type_, endings) {
    | (None, None) => Js.Nullable.undefined
    | (type_, endings) =>
      Js.Nullable.return({
        "type": type_->Js.Nullable.fromOption,
        "endings": endings->Js.Nullable.fromOption,
      })
    };
  make_(parts, options);
};