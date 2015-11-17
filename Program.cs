/* XNAWebRenderer Example Program
 * Written by Ethan "flibitijibibo" Lee
 */

using System;
using System.Runtime.InteropServices;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

class Program : Game
{
	private const string executable = "XNAWebRenderer.bin.x86_64";

	private SpriteBatch spriteBatch;
	private Texture2D texture;
	private byte[] texBuffer;
	private XNAWebRenderer.TextureUpdatedDelegate textureUpdated;
	private bool hasDrawn = false;
	private KeyboardState curState, prevState;

	private void TextureUpdated(IntPtr buffer)
	{
		Marshal.Copy(buffer, texBuffer, 0, texBuffer.Length);
		texture.SetData(texBuffer);
		hasDrawn = true;
	}

	private void CheckKeyForURL(Keys key, string URL)
	{
		if (curState.IsKeyDown(key) && !prevState.IsKeyDown(key))
		{
			XNAWebRenderer.XNAWR_LoadURL(URL);
			hasDrawn = false;
		}
	}

	public Program() : base()
	{
		GraphicsDeviceManager gdm = new GraphicsDeviceManager(this);
		gdm.PreparingDeviceSettings += PrepareDeviceSettings;
		gdm.PreferredBackBufferWidth = 1280;
		gdm.PreferredBackBufferHeight = 720;
	}

	protected override void LoadContent()
	{
		spriteBatch = new SpriteBatch(GraphicsDevice);
		texture = new Texture2D(GraphicsDevice, 1280, 720);
		texBuffer = new byte[1280 * 720 * 4];
		textureUpdated = TextureUpdated;
		XNAWebRenderer.XNAWR_Initialize(
			executable,
			"http://www.google.com/",
			textureUpdated,
			1280,
			720
		);
		prevState = Keyboard.GetState();
	}

	protected override void UnloadContent()
	{
		XNAWebRenderer.XNAWR_Shutdown();
		spriteBatch.Dispose();
		spriteBatch = null;
		texture.Dispose();
		texture = null;
	}

	protected override void Update(GameTime gameTime)
	{
		curState = Keyboard.GetState();
		CheckKeyForURL(Keys.D1, "http://www.flibitijibibo.com/");
		CheckKeyForURL(Keys.D2, "http://plus.google.com/+flibitijibibo");
		CheckKeyForURL(Keys.D3, "http://fna-xna.github.io/");
		CheckKeyForURL(Keys.D4, "http://www.github.com/flibitijibibo/XNAWebRenderer");
		CheckKeyForURL(Keys.D5, "http://store.steampowered.com/");
		CheckKeyForURL(Keys.D6, "http://www.humblebundle.com/");
		CheckKeyForURL(Keys.D7, "http://boards.4chan.org/v/");
		CheckKeyForURL(Keys.D8, "http://www.reddit.com/r/linux_gaming");
		CheckKeyForURL(Keys.D9, "http://www.nedroid.com/");
		CheckKeyForURL(Keys.D0, "http://www.metroidmetal.com/");
		base.Update(gameTime);
	}

	protected override void Draw(GameTime gameTime)
	{
		XNAWebRenderer.XNAWR_Update();
		if (hasDrawn)
		{
			spriteBatch.Begin(SpriteSortMode.Immediate, BlendState.Opaque);
			spriteBatch.Draw(texture, Vector2.Zero, Color.White);
			spriteBatch.End();
		}
		else
		{
			GraphicsDevice.Clear(Color.DarkRed);
		}
		base.Draw(gameTime);
	}

	private void PrepareDeviceSettings(object sender, PreparingDeviceSettingsEventArgs e)
	{
		e.GraphicsDeviceInformation.PresentationParameters.DepthStencilFormat = DepthFormat.None;
	}

	private static void Main(string[] args)
	{
		using (Program program = new Program())
		{
			program.Run();
		}
	}
}
