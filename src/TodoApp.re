type item = {
  title: string,
  completed: bool
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, _children) => {
    ...component,
    render: (_self) =>
      <div className="item">
        <input
          checked=(item.completed)
          /* TODO make interactive */
        />
        (ReasonReact.string(item.title))
      </div>
  };
};

type state = {items: list(item)};

type action =
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");

let newItem = () => {title: "Click a button", completed: true};

let make = (_children) => {
  ...component,
  initialState: () => {
    items: [
      {title: "Write some things to do", completed: false}
    ]
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
    },
  render: (self) => {
    let numItems = List.length(self.state.items);
    <div className="app">
      <div className="title">
        (ReasonReact.string("What to do"))
        <button onClick=(_event => self.send(AddItem))>
          (ReasonReact.string("Add something"))
        </button>
      </div>
      <div className="items">
        (
          self.state.items 
            |> List.map((item) => <TodoItem item />)
            |> Array.of_list
            |> ReasonReact.array
        )
      </div>
      <div className="items"> (ReasonReact.string("Nothing")) </div>
      <div className="footer">
        (ReasonReact.string(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};