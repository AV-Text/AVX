using System.Text;

namespace AVXFramework
{
    public class AVEngine
    {
        private Blueprint.Blue.Blueprint BlueprintLib;
        private Pinshot.Blue.PinshotLib PinshotLib;

        public AVEngine()
        {
            this.BlueprintLib = new();
            this.PinshotLib = new();
        }
        public (UInt64 cursor, string error, string result) Execute(string command)
        {
            var pinshot = this.PinshotLib.Parse(command);
            if (pinshot.root != null)
            {
                if (string.IsNullOrWhiteSpace(pinshot.root.error))
                {
                    var blueprint = this.BlueprintLib.Create(pinshot.root);

                    if (blueprint != null)
                    {
                        if (blueprint.IsValid)
                        {
                            if (blueprint.Singleton != null)
                            {
                                ; // process singleton command
                                return (0, "", "Pretend that this is the result of an executed Quelle command");
                            }
                            else if (blueprint.Commands != null)
                            {
                                UInt64 cursor = AVXFramework.NativeLibrary.create_statement(Blueprint.Blue.QStatement.Serialize(blueprint.Blueprint));
                                return (cursor, "", "");
                            }
                            else
                            {
                                return (0, "Internal Error: Unexpected blueprint encountered.", "");
                            }
                        }
                        else
                        {
                            if (blueprint.Errors.Count > 0)
                            {
                                var errors = string.Join("; ", blueprint.Errors);
                                return (0, errors, "");
                            }
                            else
                            {
                                return (0, "Blueprint was invalid, but the error list was empty.", "");
                            }
                        }
                    }
                    else
                    {
                        return (0, "Blueprint was invalid (unexpected error).", "");
                    }
                }
                else
                {
                    return (0, pinshot.root.error, "");
                }
            }
            return (0, "Unable to parse the statement.", "");
        }
    }
}